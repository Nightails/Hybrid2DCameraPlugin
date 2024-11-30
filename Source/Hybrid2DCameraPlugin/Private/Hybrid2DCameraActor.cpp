#include "Hybrid2DCameraActor.h"
#include "Kismet/GameplayStatics.h"

AHybrid2DCameraActor::AHybrid2DCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	/* Default 2D Hybrid Settings */
	Target = nullptr;
	TargetIndex = 0;
	DeadzonePadding = FVector2D::ZeroVector;
	MoveSpeed = FVector(100.f);

	PlayerController = nullptr;
	/* -------------------------- */
}

void AHybrid2DCameraActor::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerController == nullptr) PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), TargetIndex);
	PlayerController->SetViewTarget(this);
	if (Target == nullptr) Target = UGameplayStatics::GetPlayerPawn(GetWorld(), TargetIndex);
}

void AHybrid2DCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/**
	 * 1 - Check if target is out of screen bound.
	 * 2 - Get the movement direction if target is out of bound.
	 * 3 - Add movement to the camera with the direction.
	 */
	
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	FVector2D TargetScreenPosition = FVector2D::ZeroVector;
	if (!PlayerController->ProjectWorldLocationToScreen(Target->GetActorLocation(), TargetScreenPosition))
		UE_LOG(LogTemp, Warning, TEXT("Unable to covert target's position from world-space to screen-space."));
	//GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Orange, TargetScreenPosition.ToString());

	FVector MoveDirection = FVector::ZeroVector;
	// Horizontal deadzone
	if (TargetScreenPosition.X < DeadzonePadding.X) MoveDirection.X = -1.f;
	else if (TargetScreenPosition.X > (ViewportSize.X - DeadzonePadding.X)) MoveDirection.X = 1.f;
	// Vertical deadzone
	if (TargetScreenPosition.Y < DeadzonePadding.Y) MoveDirection.Y = 1.f;
	else if (TargetScreenPosition.Y > (ViewportSize.Y - DeadzonePadding.Y)) MoveDirection.Y = -1.f;
	MoveDirection.Normalize();
	//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Orange, MoveDirection.ToString());

	const FVector WorldMoveDirection = MoveDirection.X * GetActorRightVector() + MoveDirection.Y * GetActorUpVector();
	const FVector MoveToLocation = GetActorLocation() + WorldMoveDirection * MoveSpeed * DeltaTime;
	SetActorLocation(MoveToLocation);
}
