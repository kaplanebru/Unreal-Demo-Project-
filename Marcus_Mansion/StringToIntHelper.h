

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StringToIntHelper.generated.h"

/**
 * 
 */
UCLASS()
class MARCUS_MANSION_API UStringToIntHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Converts a single-character string (like "1", "2") into an integer. */
	UFUNCTION(BlueprintCallable, Category = "Conversion")
	static int32 ConvertStringToInt(const FString& InputString);

	
};
