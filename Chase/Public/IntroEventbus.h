#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CHASE_API IntroEventbus
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnEndOfSpline);
	static FOnEndOfSpline OnEndOfSpline;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCameraFadeRequest, float /*FadeDuration*/, float /*bFadeIn*/);
	static FOnCameraFadeRequest OnCameraFadeRequest;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFadeOutRequest, float /*FadeDuration*/, float /*bFadeIn*/);
	static FOnFadeOutRequest OnFadeOutRequest;

	IntroEventbus();
	~IntroEventbus();
};
