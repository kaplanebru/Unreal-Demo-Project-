

#pragma once

#include "CoreMinimal.h"
#include "IMovableTarget.h"
#include "Components/SceneComponent.h"
#include "Components/ActorComponent.h"
#include "RotatorComponent.generated.h"

DECLARE_DELEGATE(FOnRotationComplete);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARCUS_MANSION_API URotatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URotatorComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FTimerHandle RotTimerHandle;
	
	UPROPERTY()
	FRotator StartRotation;
	
	UPROPERTY()
	FRotator TargetRotation;
	
	UPROPERTY()
	float ElapsedTime;
	
	FRotator LastRotation;

	FOnRotationComplete RotationCompleteDelegate;


	UFUNCTION()
	void RotatePerStep();
	
	UFUNCTION()
	void StopTimer();
	
	UFUNCTION()
	void InitiateRotation(FRotator Target);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator Data")
	FRotator RotationAmount = FRotator(0, 180, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator Data")
	float Duration = 5;

	void StartRotationToFixedTarget(TScriptInterface<IMovableTarget> target);
	void StartRotationToFixedTargetWithEnding(TScriptInterface<IMovableTarget> target, FOnRotationComplete OnRotationComplete);
	void StartRotationToAddedTarget(TScriptInterface<IMovableTarget> target, FOnRotationComplete OnRotationComplete);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rotation")
	TScriptInterface<IMovableTarget> Target;
	
		
};
