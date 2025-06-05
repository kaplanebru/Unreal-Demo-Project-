

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MotionHelper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARCUS_MANSION_API UMotionHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UMotionHelper();

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Blueprintable, Category= "Motion")
	FTransform DestinationTransform;
		
	UFUNCTION(BlueprintCallable)
	FTransform SetDestinationTransform(USceneComponent* TargetComponent);
	
	UFUNCTION(BlueprintCallable)
	FTransform GetDestinationTransform();

	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentActor();
	
};
