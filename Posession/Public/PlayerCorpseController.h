

#pragma once
#include "Marcus_Mansion/RotatorComponent.h"
#include "Components/SceneComponent.h"
#include "PosessionEventbus.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Components/PostProcessComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



#include "CoreMinimal.h"
#include "Corpse.h"
#include "Marcus_Mansion/MoveTowardsComponent.h"
#include "GameFramework/Actor.h"
#include "Marcus_Mansion/CameraHandler.h"
#include "PlayerCorpseController.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POSESSION_API APlayerCorpseController : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerCorpseController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category="Setup")
	TSubclassOf<ACorpse> StarterCorpse;

	UPROPERTY(EditAnywhere,Category="Setup")
	URotatorComponent* Rotator;
	
	UPROPERTY(EditAnywhere,Category="Setup")
	UMoveTowardsComponent* Mover;

	UFUNCTION(BlueprintCallable, Category = "CorpseCamera")
	void RestoreCamera();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
	UCorpseControlData* CurrentControlData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
	ACorpse* CurrentCorpse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
	ACorpse* LeftCorpse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
	FVector LeftCorpsePos;

	UPROPERTY()
	ACorpse* FirstCorpse;

	UPROPERTY()
	ACharacter* PlayerCharacter;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	UCameraHandler* CameraHandler;
	
	UPROPERTY()
	UPostProcessComponent* PostProcessComp;

	UPROPERTY()
	FRotator CameraDefaultRelativeRot;

	UPROPERTY()
	FVector CameraDefaultRelativePos;

	UPROPERTY()
	bool IsRestoringCamera = false;

	
	UPROPERTY()
	UCameraComponent* Camera;

	
	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void SetCurrentCorpse(ACorpse* Corpse);

	UFUNCTION()
	void SwitchBodies(ACorpse* Corpse);

	UFUNCTION()
	void SetLeftBodyPosition();
	
	UFUNCTION()
	void OnCorpseContact(ACorpse* corpse);

	UFUNCTION()
	void ApplyPlayerRotationToCorpse();

	UFUNCTION()
	void SetCorpseControls();

	UFUNCTION()
	void RotateTowardsCorpse(TScriptInterface<IMovableTarget> Target, FRotator rotationAmount);

	UFUNCTION()
	void RotateTowards(TScriptInterface<IMovableTarget> Target, FRotator rotationAmount, bool SetEnding = true);



	UFUNCTION()
	void HandleCorpseRotationEnd();

	UFUNCTION()
	void Exit();

	FOnRotationComplete RotationCompleteDelegate;

};

