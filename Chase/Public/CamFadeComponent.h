

#pragma once

#include "IntroEventbus.h"
#include "Components/PostProcessComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "CamFadeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHASE_API UCamFadeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCamFadeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fade")
	UPostProcessComponent* FadePostProcess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fade")
	float FadeDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fade")
	float FadeWaitDuration;

	


	UPROPERTY()
	bool bIsFadingIn;

	UPROPERTY()
	float CurrentFadeTime;

	UPROPERTY()
	FTimerHandle FadeDelayTimerHandle;

	UFUNCTION(BlueprintCallable)
	void StartFade(float InFadeDuration, float InWaitDuration);

	UFUNCTION(BlueprintCallable)
	void FadeOut(float BlackDuration, float FadeOutDuration);

	UFUNCTION()
	void FadeOutAfterDelay();


	UFUNCTION()
	void UpdateFade(float DeltaTime);

	UFUNCTION()
	void UpdateBlink(float DelTaTime);


	UFUNCTION(BlueprintCallable)
	void Blink(float BlinkDuration);
	

	UFUNCTION()
	void ReverseFade();

private:
	void Setup();

	UPROPERTY()
	ACharacter* PlayerCharacter;

	UFUNCTION()
	void DelayBeforeReverse();
};
