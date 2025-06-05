


#include "MoveTowardsComponent.h"

#include "Marcus_Mansion/IMovableTarget.h"

class IMovableTarget;

UMoveTowardsComponent::UMoveTowardsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UMoveTowardsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMoveTowardsComponent::InitiateMotion(TScriptInterface<IMovableTarget> Target, FVector Destination)
{
	UE_LOG(LogTemp, Warning, TEXT("UMoveTowardsComponent::InitiateMotion"));
	if (!Target || Duration <= 0.f) return;
	TargetComponent = Target;
	
	StartPosition = TargetComponent->GetWorldLocation();
	TargetPosition = Destination;

	ElapsedTime = 0;
	GetWorld()->GetTimerManager().SetTimer(RotTimerHandle, this, &UMoveTowardsComponent::MovePerStep, 0.01f, true);
}

void UMoveTowardsComponent::MovePerStep()
{
	ElapsedTime += 0.01f;
	float Alpha = ElapsedTime / Duration;
	Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
	
	FVector NewPos = FMath::VInterpTo(StartPosition, TargetPosition, Alpha, 5.0f);


	if (Alpha >= 1.0f)
		StopTimer();

	if (NewPos.Equals(TargetPosition, 1.f))
		StopTimer();

	TargetComponent->SetWorldLocation(NewPos);
}

void UMoveTowardsComponent::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RotTimerHandle);
	TargetComponent->SetWorldLocation(TargetPosition);
}
