


#include "MotionTestActor.h"

AMotionTestActor::AMotionTestActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMotionTestActor::BeginPlay()
{
	Super::BeginPlay();
	TriggerMotion();
}