#pragma once

//#include "InputCoreTypes.h"
// #include "Engine/ //Plugins/EnhancedInputComponent.h"
// #include "EnhancedInputSubsystems.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CoreMinimal.h"
#include "IntroCharAnimInstance.h"
#include "SplineChar.h"
#include "GameFramework/Actor.h"
#include "IntroChar.generated.h"

UCLASS()
class CHASE_API AIntroChar : public AActor
{
	GENERATED_BODY()

public:
	AIntroChar();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ASplineChar* SplineChar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float InputSensitivity = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float DragInputSensitivity = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FVector2D HorizontalInputLimits = FVector2D(-60, 60); //bulunduğu posa göre belirle

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FIntPoint VerticalInputLimits = FIntPoint(-45, 45);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FVector2D DragHorizontalInputLimits = FVector2D(-60, 60); //bulunduğu posa göre belirle

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FIntPoint DragVerticalInputLimits = FIntPoint(-45, 45);

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY()
	USpringArmComponent* SpringArm;
	
	UFUNCTION()
	void SetTimersForInit();

	UFUNCTION(BlueprintCallable)
	void FadeCamera(float FadeDuration, float WaitDuration = 0);

	UFUNCTION(BlueprintCallable)
	void FadeOutCamera(float WaitDuration, float FadeDuration);

	UFUNCTION(BlueprintCallable)
	void ChangeParent();

	UFUNCTION(BlueprintCallable)
	void FreeCamera();

private:
	void Initialize();

	UPROPERTY()
	ACharacter* PlayerCharacter;
	
	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	bool bPlayerRotatingCamera = false;

	UPROPERTY()
	bool bStartedMoving = false;

	UPROPERTY()
	FTimerHandle DelayTimerHandle;

	UPROPERTY()
	FTimerHandle ControlDelayTimerHandle;

	UPROPERTY()
	FTimerHandle EnableControlTimerHandle;

	UPROPERTY()
	FVector2D PreviousMousePosition;

	UPROPERTY()
	FVector2D MousePosition = FVector2D(0, 0);

	UPROPERTY()
	bool bStartChase = false;
	
	UFUNCTION()
	void FollowSpline();

	UFUNCTION()
	void AppendInput(float DeltaTime);

	UFUNCTION()
	void SetPlayerComponents();

	UFUNCTION()
	void StartMoving();
	
	UFUNCTION()
	void EnableControl();

	UFUNCTION()
	void DisableControl();

	UFUNCTION()
	void DelayedInit();

	UFUNCTION()
	void SwitchInput();


	UFUNCTION()
	FVector2D GetMouseDeltaInput();
};
