


#include "SplinePathActor.h"

#include "IntroEventbus.h"

ASplinePathActor::ASplinePathActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	RootComponent = SplineComp;

}

void ASplinePathActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASplinePathActor::EndSpline(AActor* Other)
{
	if (!IsValid(Other)) return;

	if (IntroEventbus::OnCameraFadeRequest.IsBound())
		IntroEventbus::OnCameraFadeRequest.Broadcast(2, 1);

	// if (IntroEventbus::OnEndOfSpline.IsBound())
	// 	IntroEventbus::OnEndOfSpline.Broadcast();
	
}
