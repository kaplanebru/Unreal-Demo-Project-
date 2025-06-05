

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CorpseControlData.generated.h"

/**
 * 
 */
UCLASS()
class POSESSION_API UCorpseControlData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int32 Id;

	UPROPERTY(EditAnywhere)
	FName CorpseName;
	
	UPROPERTY(EditAnywhere)
	float Fow = 90;

	UPROPERTY(EditAnywhere)
	bool CanBeControlled = true;

	UPROPERTY(EditAnywhere)
	float CameraTilt = 0; //-10 for fox

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 200;

	UPROPERTY(EditAnywhere)
	float MaxAcceleration = 2048;

	UPROPERTY(EditAnywhere)
	FName VisionLevel;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* VisionMat;
};
