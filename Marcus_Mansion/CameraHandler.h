

#pragma once

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "IMovableTarget.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARCUS_MANSION_API UCameraHandler : public UActorComponent, public IMovableTarget
{
	GENERATED_BODY()

public:	
	UCameraHandler();

protected:
	virtual void BeginPlay() override;

public:
	virtual FVector GetRelativeLocation() const override;
	virtual void SetRelativeLocation(const FVector& NewLocation) override;
	
	virtual FRotator GetRelativeRotation() const override;
	virtual void SetRelativeRotation(const FRotator& NewRotation) override;
	
	virtual FVector GetWorldLocation() const override;
	virtual void SetWorldLocation(const FVector& NewLocation) override;

	virtual FRotator GetWorldRotation() const override;
	virtual void SetWorldRotation(const FRotator& NewRotation) override;

	

	
private:
	UPROPERTY()
	ACharacter* PlayerCharacter;

	UPROPERTY() //EditAnywhere, BlueprintReadWrite, Category = "Camera"
	TObjectPtr<USceneComponent> Camera;


	
};
