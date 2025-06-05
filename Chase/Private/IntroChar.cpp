#include "IntroChar.h"
#include "IntroEventbus.h"


AIntroChar::AIntroChar()
{
	PrimaryActorTick.bCanEverTick = true;
	Initialize();
}

void AIntroChar::Initialize()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	bPlayerRotatingCamera = false;
}


bool bCamInputDisabled = true;
FRotator FinalRotation;
float CurrentInputYaw = 0;
float CurrentInputPitch = 0;

void AIntroChar::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerComponents();
	SetTimersForInit();

	IntroEventbus::OnEndOfSpline.AddUObject(this, &AIntroChar::FreeCamera);
}

void AIntroChar::SetPlayerComponents()
{
	PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
	SpringArm = PlayerCharacter->FindComponentByClass<USpringArmComponent>();
	Camera = PlayerCharacter->FindComponentByClass<UCameraComponent>();
	PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

	//PlayerCharacter->SetActorRotation(PlayerCharacter->GetActorRotation() + FRotator(0, 90, 0));
	//HORROR ENGINE PLAYER OFFSET
}

void AIntroChar::SetTimersForInit()
{
	FTimerHandle DelayedInitHandle;
	GetWorldTimerManager().SetTimer(
		DelayedInitHandle,
		this,
		&AIntroChar::DelayedInit,
		1.0f, // 0.1s delay – enough for Horror Engine to finish overriding
		false
	);

	// GetWorldTimerManager().SetTimer(
	// 	ControlDelayTimerHandle,
	// 	this,
	// 	&AIntroChar::EnableControl,
	// 	.3f,
	// 	false
	// ); //2.1
}


void AIntroChar::DelayedInit()
{
	PreviousMousePosition = FVector2D(0, 0);
	CurrentInputPitch = 0.0f;
	CurrentInputYaw = 0.0f;

	PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	Camera->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = false;
	PlayerCharacter->bUseControllerRotationYaw = false;
	PlayerCharacter->bUseControllerRotationPitch = false;

	SpringArm->AttachToComponent(
		Root,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale
	); //!!!!!!! SPRING ARM (AND CAM) IS ATTACHED TO INTRO CHAR 

	SpringArm->SetRelativeLocation(FVector::ZeroVector);
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);

	PlayerController->SetIgnoreLookInput(true);
	PlayerController->SetIgnoreLookInput(false);

	PlayerController->SetViewTargetWithBlend(PlayerCharacter, 0.0f);
	StartMoving();
	DisableControl();
}


void AIntroChar::StartMoving()
{
	bStartedMoving = true;
}

void AIntroChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AppendInput(DeltaTime);
}


void AIntroChar::AppendInput(float DeltaTime)
{
	if (bStartedMoving)
	{
		if (bStartChase)
			FollowSpline();

		if (bPlayerRotatingCamera)
		{
			FVector2D MouseDelta = GetMouseDeltaInput();
			float InputYaw = MouseDelta.X * InputSensitivity;
			float InputPitch = -MouseDelta.Y * InputSensitivity;
			InputYaw = FMath::Clamp(InputYaw, HorizontalInputLimits.X, HorizontalInputLimits.Y);
			InputPitch = FMath::Clamp(InputPitch, VerticalInputLimits.X, VerticalInputLimits.Y);

			CurrentInputYaw += InputYaw;
			CurrentInputPitch += InputPitch;
			
			CurrentInputYaw = FMath::Clamp(CurrentInputYaw, HorizontalInputLimits.X, HorizontalInputLimits.Y);
			CurrentInputPitch = FMath::Clamp(CurrentInputPitch, VerticalInputLimits.X, VerticalInputLimits.Y);
		}
	}
	else //test
	{
		CurrentInputYaw = 0;
		CurrentInputPitch = 0;
	}
	FinalRotation = GetActorRotation() + FRotator(CurrentInputPitch, CurrentInputYaw, 0.f);
	// FinalRotation.Pitch = FMath::Clamp(FinalRotation.Pitch, VerticalInputLimits.X, VerticalInputLimits.Y);
	// FinalRotation.Yaw = FMath::Clamp(FinalRotation.Yaw, HorizontalInputLimits.X, HorizontalInputLimits.Y);
	PlayerController->SetControlRotation(FinalRotation);
}


void AIntroChar::EnableControl()
{
	//PlayerController->GetMousePosition(PreviousMousePosition.X, PreviousMousePosition.Y);
	//PlayerCharacter->bUseControllerRotationYaw = true;
	//PlayerCharacter->bUseControllerRotationPitch = true;
	//SpringArm->bUsePawnControlRotation = true;

	PlayerController->SetIgnoreLookInput(true);
	PlayerController->SetIgnoreLookInput(false);
	//bPlayerRotatingCamera = true;
}

void AIntroChar::DisableControl()
{
	PlayerCharacter->bUseControllerRotationYaw = false;
	PlayerCharacter->bUseControllerRotationPitch = false;
	SpringArm->bUsePawnControlRotation = false;
	bPlayerRotatingCamera = false;
}


void AIntroChar::SwitchInput()
{
	InputSensitivity = DragInputSensitivity;

	HorizontalInputLimits = DragHorizontalInputLimits;
	VerticalInputLimits = DragVerticalInputLimits;
}

void AIntroChar::ChangeParent()
{
	if (!IsValid(SplineChar)) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Shift parent"));

	SwitchInput();
	bPlayerRotatingCamera = false; 
	
	PreviousMousePosition = FVector2D(0, 0);
	CurrentInputPitch = 0.0f;
	CurrentInputYaw = 0.0f;

	PlayerController->SetIgnoreLookInput(true);
	PlayerController->SetIgnoreLookInput(false);
	
	// SpringArm->AttachToComponent(
	// 	SplineChar->PlayerHolder,
	// 	FAttachmentTransformRules::SnapToTargetNotIncludingScale
	// ); //!!!!!!! CAM IS ATTACHED TO SPRONG ARM
	//
	// SpringArm->SetRelativeLocation(FVector::ZeroVector);
	// SpringArm->SetRelativeRotation(FRotator(0, 0, 0));
	
	
	FollowSpline();
	SplineChar->TriggerSplineMotion();

	PreviousMousePosition = FVector2D(0, 0);
	CurrentInputPitch = 0.0f;
	CurrentInputYaw = 0.0f;
	bStartChase = true;
	bPlayerRotatingCamera = true;

	EnableControl();

}


void AIntroChar::FollowSpline() //TODO: TO Spline follower component
{
	SetActorRotation(SplineChar->PlayerHolder->GetComponentRotation()); // + FRotator(0, -90, 0));
	SetActorLocation(SplineChar->PlayerHolder->GetComponentLocation());
}

void AIntroChar::FreeCamera()
{
	SpringArm->AttachToComponent(PlayerCharacter->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	SpringArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;
	PlayerCharacter->bUseControllerRotationYaw = true;
	PlayerCharacter->bUseControllerRotationPitch = false;
	PlayerCharacter->bUseControllerRotationRoll = false;
	PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

	PlayerController->SetIgnoreLookInput(false);
	PlayerController->SetIgnoreMoveInput(false);
	PlayerController->SetViewTargetWithBlend(PlayerCharacter, 0.5f);

	// Stop ticking
	SetActorTickEnabled(false);

	// Optional safety if you ever enable it again
	bPlayerRotatingCamera = false;
}




bool bIsFirstInput = true;

FVector2D AIntroChar::GetMouseDeltaInput()
{
	if (bIsFirstInput)
	{
		bIsFirstInput = false;
		MousePosition = FVector2D(0, 0);
		PreviousMousePosition = FVector2D(0, 0);
	}

	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

	//delta (difference between current and previous positions)
	FVector2D MouseDelta = MousePosition - PreviousMousePosition;
	PreviousMousePosition = MousePosition;

	return MouseDelta;
}

void AIntroChar::FadeCamera(float FadeDuration, float WaitDuration)
{
	if (IntroEventbus::OnCameraFadeRequest.IsBound())
		IntroEventbus::OnCameraFadeRequest.Broadcast(FadeDuration, WaitDuration);
	
	//PlayerController->ClientSetCameraFade(true, FColor::Black, FVector2D(0.0f, 1.0f), FadeDuration, false);

	// FTimerHandle TimerHandle;
	// GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, FadeDuration]()
	// {
	// 	PlayerController->ClientSetCameraFade(true, FColor::Black, FVector2D(1.0f, 0.0f), FadeDuration, false);
	// }, FadeDuration + WaitDuration , false); //
}

void AIntroChar::FadeOutCamera(float WaitDuration, float FadeDuration)
{
	if (IntroEventbus::OnFadeOutRequest.IsBound())
		IntroEventbus::OnFadeOutRequest.Broadcast(WaitDuration, FadeDuration);
}
