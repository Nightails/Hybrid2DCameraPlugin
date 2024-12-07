#include "Hybrid2DCameraActor.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

AHybrid2DCameraActor::AHybrid2DCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	/* Default 2D Hybrid Settings */
	Target = nullptr;
	TargetIndex = 0;
	/* -------------------------- */

	/* Initializing Components */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	SetRootComponent(SpringArm);
	Camera->SetupAttachment(SpringArm);
	/* ----------------------- */
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
	if (LockedAxis.X) NewLocation.X = OriginPoint.X;
	if (LockedAxis.Y) NewLocation.Y = OriginPoint.Y;
	if (LockedAxis.Z) NewLocation.Z = OriginPoint.Z;
	SetActorLocation(NewLocation);
}
