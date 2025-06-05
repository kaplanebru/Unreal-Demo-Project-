#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetRotator.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POSESSION_API UTargetRotator : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetRotator();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator Data")
	float Duration = 5;

	UFUNCTION()
	void SetTargetComponent(USceneComponent* target);

	UFUNCTION()
	void StartRotationToFixedTarget(FRotator Amount);

	UPROPERTY()
	USceneComponent* TargetComponent;;

private:

	UPROPERTY()
	FTimerHandle RotTimerHandle;

	UPROPERTY()
	FRotator StartRotation;

	UPROPERTY()
	FRotator TargetRotation;

	UPROPERTY()
	float ElapsedTime;

	UFUNCTION()
	void RotateActorPerStep();

	UFUNCTION()
	void StopTimer();

	UFUNCTION()
	void InitiateRotation(FRotator Amount);
};
