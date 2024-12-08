#pragma once

#include "GameFramework/Actor.h"
#include "Hybrid2DCameraActor.generated.h"

USTRUCT(BlueprintType)
struct FWorldAxis
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	bool X = false;
	UPROPERTY(EditAnywhere)
	bool Y = false;
	UPROPERTY(EditAnywhere)
	bool Z = false;
};

UCLASS()
class HYBRID2DCAMERAPLUGIN_API AHybrid2DCameraActor : public AActor
{
	GENERATED_BODY()

public:
	AHybrid2DCameraActor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings")
	FVector OriginPoint;
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings")
	FWorldAxis LockedAxis;
	UPROPERTY(EditInstanceOnly, Category="2D Hybrid Settings")
	float CameraDistance;
	
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
	
	UPROPERTY(EditAnywhere, Category="2D Hybrid Settings|Deadzone")
	FVector DeadZoneMax;
	UPROPERTY(EditAnywhere, Category="2D Hybrid Settings|Deadzone")
	FVector DeadZoneMin;
	UPROPERTY(EditAnywhere, Category="2D Hybrid Settings|Deadzone")
	float HeightOffset;

	UPROPERTY(EditAnywhere, Category="Components")
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(EditAnywhere, Category="Components")
	TObjectPtr<class UCameraComponent> Camera;
};
