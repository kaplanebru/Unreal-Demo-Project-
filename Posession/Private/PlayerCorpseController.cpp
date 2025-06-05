#include "PlayerCorpseController.h"


class UCameraComponent;

APlayerCorpseController::APlayerCorpseController()
{
	PrimaryActorTick.bCanEverTick = false;
	Rotator = CreateDefaultSubobject<URotatorComponent>(TEXT("Rotator"));
	Mover = CreateDefaultSubobject<UMoveTowardsComponent>(TEXT("Mover"));
}

void APlayerCorpseController::BeginPlay()
{
	Super::BeginPlay();
	Initialize();

	PosessionEventbus::OnContactWithCorpse().AddUObject(this, &APlayerCorpseController::OnCorpseContact);
}

void APlayerCorpseController::Initialize()
{
	PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FirstCorpse = GetWorld()->SpawnActor<ACorpse>(StarterCorpse, FVector::Zero(), FRotator::ZeroRotator);

	if (!IsValid(PlayerCharacter)) return;
	
	PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
	PostProcessComp = PlayerCharacter->FindComponentByClass<UPostProcessComponent>();
	Camera = PlayerCharacter->FindComponentByClass<UCameraComponent>();


	if (!IsValid(FirstCorpse)) return;
	if (!IsValid(PlayerController)) return;
	if (!IsValid(Mover))return;
	if (!IsValid(Rotator)) return;
	
	CameraHandler = FindComponentByClass<UCameraHandler>();
	if (!IsValid(CameraHandler))return;

	CameraDefaultRelativePos = CameraHandler->GetRelativeLocation();//GetWorldLocation();//GetRelativeLocation();
	CameraDefaultRelativeRot = CameraHandler->GetRelativeRotation(); 

	FirstCorpse->SetActorHiddenInGame(true);
	SetCurrentCorpse(FirstCorpse);
}

void APlayerCorpseController::SetCurrentCorpse(ACorpse* Corpse)
{
	if (!IsValid(Corpse)) return;
	Corpse->SetActorEnableCollision(false);

	if (CurrentCorpse)
	{
		LeftCorpse = CurrentCorpse;
		//UE_LOG(LogTemp, Warning, TEXT("LeftCorpse Name: %s"), *LeftCorpse->GetName());
	}

	CurrentCorpse = Corpse;
	CurrentControlData = Corpse->ControlData;
}

void APlayerCorpseController::SwitchBodies(ACorpse* Corpse)
{
	SetCurrentCorpse(Corpse);
	
	// PlayerCharacter->bUseControllerRotationYaw = false;
	// PlayerCharacter->bUseControllerRotationPitch = false;
	// PlayerCharacter->bUseControllerRotationRoll = false;
	// PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	// Camera->bUsePawnControlRotation = false;
	// DetachAllSceneComponents(Camera, FDetachmentTransformRules::KeepWorldTransform);

	Mover->InitiateMotion(CameraHandler, CurrentCorpse->CamPositionIndicator->GetComponentLocation());
	RotateTowardsCorpse(CameraHandler, FRotator(0, 0, CurrentCorpse->HeadRelativeRotation));
}


void APlayerCorpseController::ApplyPlayerRotationToCorpse()
{
	FRotator CorpseRotation = CurrentCorpse->CamPositionIndicator->GetComponentRotation();
	CorpseRotation.Pitch += CurrentControlData->CameraTilt;
	CorpseRotation.Yaw += 90.0f; //player offset

	PlayerCharacter->GetController()->SetControlRotation(CorpseRotation);
}

void APlayerCorpseController::RotateTowardsCorpse(TScriptInterface<IMovableTarget> Target, FRotator rotationAmount)
{
	IsRestoringCamera = false;
	RotationCompleteDelegate.BindUObject(this, &APlayerCorpseController::HandleCorpseRotationEnd);
	RotateTowards(Target, rotationAmount);
}


void APlayerCorpseController::RotateTowards(TScriptInterface<IMovableTarget> Target, FRotator rotationAmount,
                                            bool SetEnding)
{
	Rotator->RotationAmount = rotationAmount;
	if (SetEnding)
		Rotator->StartRotationToFixedTargetWithEnding(Target, RotationCompleteDelegate);
	else
		Rotator->StartRotationToFixedTarget(Target);
}

void APlayerCorpseController::RestoreCamera()
{
	IsRestoringCamera = true;
	RotationCompleteDelegate.Unbind();

	CameraHandler->SetRelativeLocation(CameraDefaultRelativePos);
	CameraHandler->SetRelativeRotation(CameraDefaultRelativeRot);

	SetLeftBodyPosition();
}


void APlayerCorpseController::HandleCorpseRotationEnd()
{
	if (IsRestoringCamera) return;
	UE_LOG(LogTemp, Display, TEXT("HandleCorpseRotationEnd"));

	PlayerController->ClientSetCameraFade(true, FColor::Black, FVector2D(1.0f, 0.0f), 5.0f, true);
	CurrentCorpse->SetActorHiddenInGame(true);
	ApplyPlayerRotationToCorpse();
	SetCorpseControls();
}

void APlayerCorpseController::Exit()
{
	UE_LOG(LogTemp, Error, TEXT("Game over due to an error."));
	Destroy();
}


void APlayerCorpseController::SetLeftBodyPosition()
{
	if (!IsValid(LeftCorpse)) return;

	FVector pos = PlayerCharacter->GetActorLocation();
	
	FVector ForwardDirection = PlayerCharacter->GetActorForwardVector();
	pos += ForwardDirection * 100;
	pos.Z = 0;
	LeftCorpsePos = pos;
	
	LeftCorpse->SetActorLocation(LeftCorpsePos);
	LeftCorpse->IsCorpse = false;
	// LeftCorpse->SetActorHiddenInGame(false);
	// LeftCorpse->SetAnimationStartState();
}

void APlayerCorpseController::OnCorpseContact(ACorpse* corpse)
{
	if (!IsValid(corpse)) return;
	SwitchBodies(corpse);
}

void APlayerCorpseController::SetCorpseControls()
{
	if (PostProcessComp)
	{
		if (LeftCorpse->ControlData->VisionMat)
			PostProcessComp->Settings.RemoveBlendable(LeftCorpse->ControlData->VisionMat);

		if (!CurrentControlData->VisionMat) return;

		if (LeftCorpse->ControlData->VisionMat)
			PostProcessComp->Settings.RemoveBlendable(LeftCorpse->ControlData->VisionMat);

		PostProcessComp->Settings.AddBlendable(CurrentControlData->VisionMat, 1.0f);
	}

	LeftCorpse->HideVisionLevel();
	CurrentCorpse->ShowVisionLevel();
	
}
