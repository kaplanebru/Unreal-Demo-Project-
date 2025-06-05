#pragma once
 
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMovableTarget.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UMovableTarget: public UInterface
{
	GENERATED_BODY()
};

class IMovableTarget
{
	GENERATED_BODY()
 
public:
	virtual FVector GetRelativeLocation() const = 0;
	
	virtual void SetRelativeLocation(const FVector& NewLocation) = 0;
	
	virtual FRotator GetRelativeRotation() const = 0;
	
	virtual void SetRelativeRotation(const FRotator& NewRotation) = 0;
	
	virtual FVector GetWorldLocation() const = 0;

	virtual void SetWorldLocation(const FVector& NewLocation) = 0;

	virtual FRotator GetWorldRotation() const = 0;

	virtual void SetWorldRotation(const FRotator& NewRotation) = 0;
	
};