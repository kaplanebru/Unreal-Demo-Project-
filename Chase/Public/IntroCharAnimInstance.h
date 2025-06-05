

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IntroCharAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EIntroCharAnimStates : uint8
{
	Idle1   UMETA(DisplayName = "Idle1"),
	Moving  UMETA(DisplayName = "Moving"),
	Idle2   UMETA(DisplayName = "Idle2"),
	Scare  UMETA(DisplayName = "Scare")
};

UCLASS()
class CHASE_API UIntroCharAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	EIntroCharAnimStates CurrentState;

	UFUNCTION()
	void SetAnimState(EIntroCharAnimStates State);
	
};
