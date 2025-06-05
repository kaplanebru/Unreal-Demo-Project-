

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "SplinePathActor.generated.h"

UCLASS()
class CHASE_API ASplinePathActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASplinePathActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* SplineComp;

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void EndSpline(AActor* Other);
};
