


#include "IntroController.h"


#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"


AIntroController::AIntroController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AIntroController::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
	
}

void AIntroController::Initialize()
{
	PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
	SpringArm = PlayerCharacter->FindComponentByClass<USpringArmComponent>();
	
	Camera = PlayerCharacter->FindComponentByClass<UCameraComponent>();
	
	//PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	// PlayerCharacter->DisableInput(PlayerController);
	//
	// if (!IsValid(LevelSequenceActor)) return;
	// if (!IsValid(PlayerCharacter)) return;
	// PlayerController->SetIgnoreLookInput(true);
	// PlayerController->SetIgnoreMoveInput(true);
	// LevelSequenceActor->SetBindingByTag(TEXT("IntroPlayer"), { PlayerController });

	//Camera->SetRelativeRotation(FRotator(180, 0, 0));

	// if (IsValid(IntroChar))
	// 	IntroChar->SetTimersForInit();

	
}


