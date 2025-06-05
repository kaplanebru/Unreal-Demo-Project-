

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionTestActor.generated.h"

UCLASS(Blueprintable)
class CHASE_API AMotionTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMotionTestActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Motion")
	FVector DestinationToMove;

	UFUNCTION(BlueprintImplementableEvent, Category="Motion")
	void TriggerMotion();

protected:
	virtual void BeginPlay() override;

	



};
