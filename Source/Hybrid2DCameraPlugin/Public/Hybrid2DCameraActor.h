#pragma once

#include "Camera/CameraActor.h"
#include "Hybrid2DCameraActor.generated.h"

UCLASS()
class HYBRID2DCAMERAPLUGIN_API AHybrid2DCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	AHybrid2DCameraActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/**
	 * Target to follow.
	 * The target will be automatically assigned at BeginPlay(). So assigning in the editor is only for setup/debugging purposes.
	 */
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings|Target")
	TObjectPtr<AActor> Target;
	/**
	 * Follow target 0 by default.
	 */
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings|Target")
	int TargetIndex;

	UPROPERTY(EditAnywhere, Category="2D Hybrid Settings")
	FVector2D DeadzonePadding;

	/**
	 * How fast the camera try to catch up to the target.
	 */
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings")
	FVector MoveSpeed;

	UPROPERTY()
	APlayerController* PlayerController;
};
