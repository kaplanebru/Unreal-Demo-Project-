


#include "TargetRotator.h"


UTargetRotator::UTargetRotator()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTargetRotator::BeginPlay()
{
	Super::BeginPlay();

	
}

void UTargetRotator::SetTargetComponent(USceneComponent* target)
{
	TargetComponent = target;
}


void UTargetRotator::StartRotationToFixedTarget(FRotator Amount)
{
	if (!IsValid(TargetComponent)) return;
	
	//RotationCompleteDelegate = OnRotationComplete;
	InitiateRotation(Amount);
}

void UTargetRotator::InitiateRotation(FRotator Amount)
{
	ElapsedTime = 0;
	StartRotation = TargetComponent->GetRelativeRotation();// TODO: !!!!!!important so that it wont start from zero!!!
	TargetRotation = Amount;
	GetWorld()->GetTimerManager().SetTimer(RotTimerHandle, this, &UTargetRotator::RotateActorPerStep, 0.01f, true);
}

void UTargetRotator::RotateActorPerStep()
{
	if (!GetOwner()) return;

	ElapsedTime += 0.01f;
	float Ease = ElapsedTime / Duration;
	Ease = FMath::Clamp(Ease, 0.0f, 1.0f);

	FRotator NewRot = FMath::RInterpTo(StartRotation, TargetRotation, Ease, 5.0f);

	
	if (Ease >= 1.0f)
		StopTimer();

	// if (NewRot.Equals(TargetRotation, 1.f))
	// 	StopTimer();

	TargetComponent->SetRelativeRotation(NewRot);
}

void UTargetRotator::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RotTimerHandle);
	
	TargetComponent->SetRelativeRotation(TargetRotation);
}




