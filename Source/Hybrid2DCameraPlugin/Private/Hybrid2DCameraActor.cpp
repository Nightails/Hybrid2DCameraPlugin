#include "Hybrid2DCameraActor.h"
#include "Kismet/GameplayStatics.h"

AHybrid2DCameraActor::AHybrid2DCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	/* Default 2D Hybrid Settings */
	Target = nullptr;
	TargetIndex = 0;
	LockAxis.Y = true;
	OriginLocation = FVector::ZeroVector;
	OriginRotation = FRotator::ZeroRotator;
	CameraDistance = 0.f;
	/* -------------------------- */
}

void AHybrid2DCameraActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	OriginLocation = Transform.GetLocation();
	OriginRotation = Transform.GetRotation().Rotator();
	CameraDistance = FindCameraDistance();
}

void AHybrid2DCameraActor::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* Controller  = UGameplayStatics::GetPlayerController(GetWorld(), TargetIndex))
		Controller->SetViewTarget(this);
	if (Target == nullptr)
	{
		Target = UGameplayStatics::GetPlayerPawn(GetWorld(), TargetIndex);
		CameraDistance = FindCameraDistance();
	}
}

void AHybrid2DCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AHybrid2DCameraActor::FindCameraDistance() const
{
	if (Target == nullptr) return 0.f;
	return (GetActorLocation() - Target->GetActorLocation()).Size();
}


