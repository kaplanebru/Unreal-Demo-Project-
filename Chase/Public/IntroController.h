

#pragma once
#include "MovieSceneObjectBindingID.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "IntroChar.h"
#include "LevelSequenceActor.h"
#include "GameFramework/Actor.h"
#include "IntroController.generated.h"

UCLASS()
class CHASE_API AIntroController : public AActor
{
	GENERATED_BODY()
	
public:	
	AIntroController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro")
	AIntroChar* IntroChar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro")

	ALevelSequenceActor* LevelSequenceActor;

private:
	UPROPERTY()
	ACharacter* PlayerCharacter;

	UPROPERTY()
	USpringArmComponent* SpringArm;



	UPROPERTY()
	APlayerController* PlayerController;

	UFUNCTION()
	void Initialize();
};
