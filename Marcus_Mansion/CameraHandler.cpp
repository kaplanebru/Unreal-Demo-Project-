


#include "CameraHandler.h"



UCameraHandler::UCameraHandler()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UCameraHandler::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Camera = Cast<USceneComponent>(PlayerCharacter->FindComponentByClass<UCameraComponent>());
}

FVector UCameraHandler::GetRelativeLocation() const
{
	return Camera ? Camera->GetRelativeLocation() : FVector::ZeroVector;
}

void UCameraHandler::SetRelativeLocation(const FVector& NewLocation)
{
	if (Camera)
	{
		Camera->SetRelativeLocation(NewLocation);
	}
}

FRotator UCameraHandler::GetRelativeRotation() const
{
	return Camera ? Camera->GetRelativeRotation() : FRotator::ZeroRotator;
}

void UCameraHandler::SetRelativeRotation(const FRotator& NewRotation)
{
	if (Camera)
	{
		Camera->SetRelativeRotation(NewRotation);
	}
}

FVector UCameraHandler::GetWorldLocation() const
{
	return Camera ? Camera->GetComponentLocation() : FVector::ZeroVector;
}

void UCameraHandler::SetWorldLocation(const FVector& NewLocation)
{
	if (Camera)
	{
		Camera->SetWorldLocation(NewLocation);
	}
}

FRotator UCameraHandler::GetWorldRotation() const
{
	return Camera ? Camera->GetComponentRotation() : FRotator::ZeroRotator;
}

void UCameraHandler::SetWorldRotation(const FRotator& NewRotation)
{
	if (Camera)
	{
		Camera->SetWorldRotation(NewRotation);
	}
}
