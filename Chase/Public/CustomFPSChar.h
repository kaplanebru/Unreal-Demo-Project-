

#pragma once
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "EnhancedInputComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomFPSChar.generated.h"

UCLASS()
class CHASE_API ACustomFPSChar : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomFPSChar();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookUp(float Value);
	void Turn(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	// Optional for cinematic blending
	void SetCinematicControl(bool bEnabled);

private:
	bool bCinematicControl = false;
};


