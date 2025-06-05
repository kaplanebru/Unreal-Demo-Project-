

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISelectable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class USelectable : public UInterface //class MARCUS_MANSION_API USelectable : public UInterface
{
	GENERATED_BODY()
	
};

class ISelectable
{
	GENERATED_BODY()

public:
	virtual void ExecuteSelection(FHitResult& Hit) = 0;

	virtual void SetWorldLocation(const FVector& NewLocation) = 0;

	virtual void SetWorldRotation(const FRotator& NewRotation) = 0;

	virtual FVector GetWorldLocation() const = 0;

	virtual FRotator GetWorldRotation() const = 0;

	virtual void SetCollision(bool Enable) = 0;

	virtual void Fall() = 0;

	virtual void Hide() = 0;

	virtual void Show() = 0;

	virtual void BePlaced() = 0;
 
};
