

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CorpseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class POSESSION_API UCorpseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	bool bIsInCorpseState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	bool bIsDying = false;
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetCorpseState(bool StartAsACorpse);
	
	
};
