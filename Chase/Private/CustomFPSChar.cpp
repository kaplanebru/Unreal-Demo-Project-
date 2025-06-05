
#include "CustomFPSChar.h"

ACustomFPSChar::ACustomFPSChar()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCastShadow(false);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	// Enable yaw control by controller
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

}

void ACustomFPSChar::BeginPlay()
{
	Super::BeginPlay();
	SetCinematicControl(false);
}


void ACustomFPSChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCinematicControl)
	{
		// Optional blending logic here (e.g., slowly rotate toward a cinematic target)
	}
}

void ACustomFPSChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent->BindAxis("MoveForward", this, &ACustomFPSChar::MoveForward);
	// PlayerInputComponent->BindAxis("MoveRight", this, &ACustomFPSChar::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACustomFPSChar::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACustomFPSChar::LookUp);
}

void ACustomFPSChar::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ACustomFPSChar::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ACustomFPSChar::Turn(float Value)
{
	if (!bCinematicControl)
		AddControllerYawInput(Value);
}

void ACustomFPSChar::LookUp(float Value)
{
	if (!bCinematicControl)
		AddControllerPitchInput(Value);
}

void ACustomFPSChar::SetCinematicControl(bool bEnabled)
{
	bCinematicControl = bEnabled;
}