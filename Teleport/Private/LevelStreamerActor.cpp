#include "LevelStreamerActor.h"
#include "Engine/Engine.h"

ALevelStreamerActor::ALevelStreamerActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALevelStreamerActor::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));//UGameplayStatics::GetPlayerCharacter(this, 0);
}


void ALevelStreamerActor::AfterOverlapBegins(AActor* OtherActor)
{
	if (!OtherActor || !Character)
	{
		return;
	}

	if (LevelsToLoad.Num() > 0 && OtherActor == Character)
	{
		for (const FName& LevelToLoad : LevelsToLoad)
		{
			if (!LevelToLoad.IsNone())
			{
				FLatentActionInfo LatentInfo;
				LatentInfo.CallbackTarget = this;
				UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);

				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("LOAD ") + LevelToLoad.ToString());
			}
		}
	}

	if (OtherActor == Character)
	{
		
		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ALevelStreamerActor::UnloadLevels, 1.0f, false);
		}
	}
	
}

void ALevelStreamerActor::UnloadLevels()
{
	if (LevelsToUnload.Num() > 0)
	{
		for (const FName& LevelToUnload : LevelsToUnload)
		{
			if (!LevelToUnload.IsNone())
			{
				FLatentActionInfo LatentInfo;
				LatentInfo.CallbackTarget = this;
				UGameplayStatics::UnloadStreamLevel(this, LevelToUnload, LatentInfo, true);

				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UNLOAD ") + LevelToUnload.ToString());
			}
		}
	}
}

void ALevelStreamerActor::AfterOverlapEnds(AActor* OtherActor)
{
	
}
