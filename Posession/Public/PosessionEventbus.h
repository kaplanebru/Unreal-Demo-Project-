

#pragma once

#include "CoreMinimal.h"
#include "Corpse.h"

/**
 * 
 */
class POSESSION_API PosessionEventbus
{
public:
	// Declare the static event (delegate)
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnContactWithCorpse, ACorpse*);

	// Static function to access the event
	static FOnContactWithCorpse& OnContactWithCorpse()
	{
		static FOnContactWithCorpse Event;
		return Event;
	}
};

UENUM(BlueprintType)
enum class ECorpseState : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	CorpseState UMETA(DisplayName = "CorpseState"),
	Dead        UMETA(DisplayName = "Dead")
};