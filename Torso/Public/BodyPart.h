

#pragma once

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "Enums.h"
#include "GameFramework/Actor.h"
#include "Marcus_Mansion/ISelectable.h"
#include "BodyPart.generated.h"

UCLASS()
class TORSO_API ABodyPart : public AActor, public ISelectable
{
	GENERATED_BODY()
	
public:	
	ABodyPart();

protected:
	virtual void BeginPlay() override;

public:
	virtual void ExecuteSelection(FHitResult& Hit) override;
	virtual void SetWorldLocation(const FVector& NewLocation) override;
	virtual void SetWorldRotation(const FRotator& NewRotation) override;
	virtual FVector GetWorldLocation() const override;
	virtual FRotator GetWorldRotation() const override;
	virtual void SetCollision(bool Enable) override;
	virtual void Fall()override;
	virtual void Hide()override;
	virtual void Show()override;
	virtual void BePlaced()override;



	
	UPROPERTY(EditAnywhere)
	EBodyPart Type;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Torso")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Torso")
	UBoxComponent* Trigger;

	UPROPERTY()
	ACharacter* PlayerCharacter;
	
	UFUNCTION()
	void Initiate();

	
private:
	UPROPERTY()
	USceneComponent* Root;
};
