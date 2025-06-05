

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MARCUS_MANSION_API CommonEventbus
{
public:


	DECLARE_DELEGATE(FOnPlaceObjectRequest);
	static FOnPlaceObjectRequest OnPlaceObjectRequest;
	
	
	CommonEventbus();
	~CommonEventbus();
};
