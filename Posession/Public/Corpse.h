#pragma once

#include "CorpseAnimInstance.h"
#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "CorpseControlData.h"
#include "GameFramework/Actor.h"
#include "Corpse.generated.h"

class URotatorComponent;

UCLASS(Blueprintable, BlueprintType)
class POSESSION_API ACorpse : public AActor
{
	GENERATED_BODY()

public:
	ACorpse();

protected:
	virtual void BeginPlay() override;

public:
	//UPROPERTY(meta = (DeprecateProperty, DeprecatedMessage = "ControlData is deprecated and will be removed soon."))

	UPROPERTY(EditAnywhere)
	UCorpseControlData* ControlData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Corpse")
	float HeadRelativeRotation = 90;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Corpse")
	USceneComponent* CamPositionIndicator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Corpse")
	FVector CamPosition;

	UPROPERTY()
	USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Corpse")
	UAnimMontage* EntryMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Corpse")
	UAnimMontage* PlayDeadMontage;

	UPROPERTY()
	bool IsCorpse = true;

	UFUNCTION()
	void SetAnimationStartState();

	UFUNCTION(BlueprintCallable, Category = "Corpse")
	ACorpse* NotifyContact();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Corpse", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UFUNCTION()
	void ShowVisionLevel();

	UFUNCTION()
	void HideVisionLevel();

private:
	UPROPERTY()
	UAnimInstance* AnimInstance;

	UPROPERTY()
	UCorpseAnimInstance* CorpseAnimInstance;

	UFUNCTION()
	void SetCamPosition();

	UFUNCTION()
	void Setup();

	UFUNCTION()
	USkeletalMeshComponent* GetSkeletalMeshComponent(AActor* Actor);

};
