


#include "MotionHelper.h"

UMotionHelper::UMotionHelper()
{

	PrimaryComponentTick.bCanEverTick = false;
}


void UMotionHelper::BeginPlay()
{
	Super::BeginPlay();

}

FTransform UMotionHelper::SetDestinationTransform(USceneComponent* TargetComponent)
{
	DestinationTransform = TargetComponent->GetComponentTransform();
	return DestinationTransform;
}

FTransform UMotionHelper::GetDestinationTransform()
{
	return DestinationTransform;
}

AActor* UMotionHelper::GetCurrentActor()
{
	if (GetOwner() != nullptr)
	{
		return GetOwner();
	}
	else
	{
		return nullptr;
	}
}
