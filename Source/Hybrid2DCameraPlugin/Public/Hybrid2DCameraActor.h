#pragma once

#include "Camera/CameraActor.h"
#include "Hybrid2DCameraActor.generated.h"

USTRUCT(BlueprintType)
struct FLockAxis
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool X = false;
	UPROPERTY(EditAnywhere)
	bool Y = false;
	UPROPERTY(EditAnywhere)
	bool Z = false;
};

USTRUCT(BlueprintType)
struct FDeadzoneRange
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float Min = -10.f;
	UPROPERTY(EditAnywhere)
	float Max = 10.f;
};

UCLASS()
class HYBRID2DCAMERAMODULE_API AHybrid2DCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	AHybrid2DCameraActor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/**
	 * Target to follow.
	 * The target will be automatically assigned at BeginPlay(). So assign in the editor is only for setup/debugging purpose.
	 */
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings|Target")
	TObjectPtr<AActor> Target;
	/**
	 * Follow target 0 by default.
	 */
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings|Target")
	int TargetIndex;

	/**
	 * More than one axis can be locked.
	 */
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings|Lock Transform")
	FLockAxis LockAxis;
	/**
	 * Original location to be used with the LockAxis.
	 */
	UPROPERTY(VisibleAnywhere, Category="2D Hybrid Settings|Lock Transform")
	FVector OriginLocation;
	/**
	 * Original rotation to be used with the LockAxis.
	 */
	UPROPERTY(VisibleAnywhere, Category="2D Hybrid Settings|Lock Transform")
	FRotator OriginRotation;
	/**
	 * Distance from camera to the Target.
	 * Intend for camera that also track target in Depth axis.
	 */
	UPROPERTY(VisibleAnywhere, Category="2D Hybrid Settings|Lock Transform")
	float CameraDistance;

	/**
	 * Horizontal deadzone in screen-space.
	 */
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings|Deadzone")
	FDeadzoneRange HorizontalDeadzone;
	/**
	 * Vertical deadzone in screen-space.
	 */
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings|Deadzone")
	FDeadzoneRange VerticalDeadzone;

	float FindCameraDistance() const;
};
