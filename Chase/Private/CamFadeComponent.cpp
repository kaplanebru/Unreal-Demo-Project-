#include "CamFadeComponent.h"


UCamFadeComponent::UCamFadeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCamFadeComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FadePostProcess = PlayerCharacter->FindComponentByClass<UPostProcessComponent>();

	Setup();
	IntroEventbus::OnCameraFadeRequest.AddUObject(this, &UCamFadeComponent::StartFade);
	IntroEventbus::OnFadeOutRequest.AddUObject(this, &UCamFadeComponent::FadeOut);
}


void UCamFadeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateFade(DeltaTime);
}

void UCamFadeComponent::Setup()
{
	FadePostProcess->bUnbound = true;

	FadePostProcess->Settings.bOverride_ColorSaturation = true;
	FadePostProcess->Settings.ColorSaturation = FVector4(0.f, 0.f, 0.f, 0.f);

	FadePostProcess->Settings.bOverride_SceneColorTint = true;
	FadePostProcess->Settings.SceneColorTint = FLinearColor::Black;

	FadePostProcess->BlendWeight = 0.0f;
}


void UCamFadeComponent::StartFade(float InFadeDuration, float InWaitDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("START FADE"));
	FadeDuration = InFadeDuration;
	FadeWaitDuration = InWaitDuration;
	bIsFadingIn = true;
	CurrentFadeTime = 0.0f;

	PrimaryComponentTick.bCanEverTick = true;
}

void UCamFadeComponent::UpdateFade(float DeltaTime)
{
	if (!FadePostProcess) return;

	CurrentFadeTime += DeltaTime;
	float Progress = FMath::Clamp(CurrentFadeTime / FadeDuration, 0.0f, 1.0f);

	if (bIsFadingIn)
	{
		FadePostProcess->BlendWeight = Progress;
	}
	else
	{
		FadePostProcess->BlendWeight = 1.0f - Progress;
	}

	if (Progress >= 1.0f)
	{
		if (bIsFadingIn)
		{
			PrimaryComponentTick.bCanEverTick = false;
			DelayBeforeReverse();
		}
		else
		{
			PrimaryComponentTick.bCanEverTick = false;
			FadePostProcess->BlendWeight = 0.0f;
		}
	}
}
void UCamFadeComponent::DelayBeforeReverse()
{
	//GetWorld()->GetTimerManager().SetTimer(FadeDelayTimerHandle, this, &UCamFadeComponent::ReverseFade, FadeWaitDuration, false);
	if (!GetWorld()->GetTimerManager().IsTimerActive(FadeDelayTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(
			FadeDelayTimerHandle,
			this,
			&UCamFadeComponent::ReverseFade,
			FadeWaitDuration,
			false
		);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
										 FString::Printf(TEXT("Timer Set for %.2f seconds"), FadeWaitDuration));
	}
}

void UCamFadeComponent::ReverseFade()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ReverseFade called"));
	UE_LOG(LogTemp, Warning, TEXT("ReverseFade called"));

	bIsFadingIn = false;
	CurrentFadeTime = 0.0f;
	PrimaryComponentTick.bCanEverTick = true;
}

void UCamFadeComponent::FadeOut(float BlackDuration, float FadeOutDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("FADE OUT"));

	PrimaryComponentTick.bCanEverTick = false;
	FadeWaitDuration = BlackDuration;
	FadeDuration = FadeOutDuration;
	CurrentFadeTime = 0.0f;

	FadePostProcess->BlendWeight = 0.0f;

	if (!GetWorld()->GetTimerManager().IsTimerActive(FadeDelayTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(
			FadeDelayTimerHandle,
			this,
			&UCamFadeComponent::FadeOutAfterDelay,
			FadeWaitDuration,
			false
		);
	}
}

void UCamFadeComponent::FadeOutAfterDelay()
{
	FadePostProcess->BlendWeight = 0.0f;
	PrimaryComponentTick.bCanEverTick = true;
}

void UCamFadeComponent::Blink(float BlinkDuration)
{
	FadeDuration = BlinkDuration;
	FadePostProcess->BlendWeight = 0.0f;

	CurrentFadeTime = 0.0f;
}




void UCamFadeComponent::UpdateBlink(float DelTaTime)
{
}


