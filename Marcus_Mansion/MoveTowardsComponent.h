

#pragma once

#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveTowardsComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = (Rendering, Replication, Input, Collision))
class MARCUS_MANSION_API UMoveTowardsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoveTowardsComponent();

protected:
	virtual void BeginPlay() override;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Data")
	FVector TargetPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Data")
	float Duration = 5;

	UPROPERTY()
	TScriptInterface<IMovableTarget> TargetComponent;

	UFUNCTION()
	void InitiateMotion(TScriptInterface<IMovableTarget> Target, FVector Destination);
	

private:
	UPROPERTY()
	FTimerHandle RotTimerHandle;
	
	UPROPERTY()
	FVector StartPosition;
	
	UPROPERTY()
	float ElapsedTime;
	
	UFUNCTION()
	void MovePerStep();

	UFUNCTION()
	void StopTimer();


		
};
