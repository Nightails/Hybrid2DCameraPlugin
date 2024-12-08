#include "Hybrid2DCameraActor.h"

#include "Hybrid2DCameraUtility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AHybrid2DCameraActor::AHybrid2DCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	/* Default 2D Hybrid Settings */
	OriginPoint = FVector::ZeroVector;
	LockedAxis.Y = true;
	CameraDistance = 500.f;
	
	Target = nullptr;
	TargetIndex = 0;

	DeadZoneMax = FVector::ZeroVector;
	DeadZoneMin = FVector::ZeroVector;
	HeightOffset = 50.f;
	/* -------------------------- */

	/* Initializing Components */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	SetRootComponent(SpringArm);
	Camera->SetupAttachment(SpringArm);
	/* ----------------------- */
}

void AHybrid2DCameraActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SpringArm->TargetArmLength = CameraDistance;
	SpringArm->TargetOffset.Z = HeightOffset;
}

void AHybrid2DCameraActor::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), TargetIndex);
	PlayerController->SetViewTarget(this);
	if (Target == nullptr) Target = UGameplayStatics::GetPlayerPawn(GetWorld(), TargetIndex);
}

void AHybrid2DCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Target == nullptr) return;
	FVector NewLocation = Target->GetActorLocation();
	NewLocation.X = FHybrid2DCameraUtility::GetFloatValueWithinRange(
		GetActorLocation().X, NewLocation.X, DeadZoneMin.X, DeadZoneMax.X);
	NewLocation.Y = FHybrid2DCameraUtility::GetFloatValueWithinRange(
		GetActorLocation().Y, NewLocation.Y, DeadZoneMin.Y, DeadZoneMax.Y);
	NewLocation.Z = FHybrid2DCameraUtility::GetFloatValueWithinRange(
		GetActorLocation().Z, NewLocation.Z, DeadZoneMin.Z, DeadZoneMax.Z);
	if (LockedAxis.X) NewLocation.X = OriginPoint.X;
	if (LockedAxis.Y) NewLocation.Y = OriginPoint.Y;
	if (LockedAxis.Z) NewLocation.Z = OriginPoint.Z;
	const FVector SmoothLocation = UKismetMathLibrary::VInterpTo(
		GetActorLocation(), NewLocation, DeltaTime, 10.f);
	SetActorLocation(SmoothLocation);
}

