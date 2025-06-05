// Enums.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums.generated.h"

// Enum must be defined outside the class to be used properly with UENUM
UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	LeftArm   UMETA(DisplayName = "Left Arm"),
	RightArm  UMETA(DisplayName = "Right Arm"),
	LeftLeg   UMETA(DisplayName = "Left Leg"),
	RightLeg  UMETA(DisplayName = "Right Leg")
};

// Class to hold the enum (Optional for organization or extending functionality)
UCLASS(BlueprintType)
class TORSO_API UBodyParts : public UObject
{
	GENERATED_BODY()

public:
	// This can hold references, methods, or other useful data related to the body parts
};
