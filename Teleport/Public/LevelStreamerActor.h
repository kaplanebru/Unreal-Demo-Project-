

#pragma once

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamerActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
//UCLASS()
class TELEPORT_API ALevelStreamerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelStreamerActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Streamer")
	bool bIsSpawning = false;
	
	UFUNCTION(BlueprintCallable)
	void AfterOverlapBegins(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void AfterOverlapEnds(AActor* OtherActor);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<FName> LevelsToLoad;

	UPROPERTY(EditAnywhere)
	TArray<FName> LevelsToUnload;

private:
	UPROPERTY()
	ACharacter* Character;

	UFUNCTION()
	void UnloadLevels();

	UPROPERTY()
	FTimerHandle TimerHandle;

	
};
