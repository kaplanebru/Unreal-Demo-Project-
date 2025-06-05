#pragma once

#include "RotatorComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

URotatorComponent::URotatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URotatorComponent::BeginPlay()
{
	Super::BeginPlay();
}


void URotatorComponent::StartRotationToFixedTarget(TScriptInterface<IMovableTarget> target)
{
	if (!target) return;
	Target = target;
	InitiateRotation(RotationAmount);
}

void URotatorComponent::StartRotationToFixedTargetWithEnding(TScriptInterface<IMovableTarget> target, FOnRotationComplete OnRotationComplete)
{
	if (!target) return;
	StartRotationToFixedTarget(target);
	RotationCompleteDelegate = OnRotationComplete;
}

void URotatorComponent::StartRotationToAddedTarget(TScriptInterface<IMovableTarget> target, FOnRotationComplete OnRotationComplete)
{
	if (!target) return;
	Target = target;

	RotationCompleteDelegate = OnRotationComplete;
	InitiateRotation(StartRotation + RotationAmount);
}



void URotatorComponent::InitiateRotation(FRotator TargetRot)
{

	StartRotation = Target->GetRelativeRotation();  //TODO: !!!!!!important so that it wont start from zero!!!
	TargetRotation = TargetRot;

	ElapsedTime = 0;
	GetWorld()->GetTimerManager().SetTimer(RotTimerHandle, this, &URotatorComponent::RotatePerStep, 0.01f, true);
}

void URotatorComponent::RotatePerStep()
{
	if (!GetOwner()) return;

	ElapsedTime += 0.01f;
	float Ease = ElapsedTime / Duration;
	Ease = FMath::Clamp(Ease, 0.0f, 1.0f);

	FRotator NewRot = FMath::RInterpTo(StartRotation, TargetRotation, Ease, 5.0f);


	if (Ease >= 1.0f)
		StopTimer();

	if (NewRot.Equals(TargetRotation, 1.f))
		StopTimer();

	if (Target)
		Target->SetRelativeRotation(NewRot);//SetWorldRotation(NewRot);//SetRelativeRotation(NewRot);
	
	
}

void URotatorComponent::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RotTimerHandle);

	if (Target)
		Target->SetRelativeRotation(TargetRotation);//SetWorldRotation(TargetRotation);//SetRelativeRotation(TargetRotation);

	if (RotationCompleteDelegate.IsBound())
	{
		RotationCompleteDelegate.Execute();
	}
}
