

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TELEPORT_API USpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpawnerComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FRotator SpawnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	bool bHasFXBefore = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float EffectDelay = 0;

	UFUNCTION(BlueprintCallable)
	void SpawnToNewLocation(AActor* OtherActor);

	
private:
	UPROPERTY()
	FTimerHandle DelayTimerHandle;

	UPROPERTY()
	AActor* ActorToSpawn;

	UFUNCTION()
	void PlayEffect();

	UFUNCTION()
	void DelaySpawning();

	UFUNCTION()
	void Spawn();

	UPROPERTY()
	APlayerController* Controller;

	UFUNCTION()
	void EnableActorInput(AActor* Actor);

	UFUNCTION()
	void DisableActorInput(AActor* Actor);
		
};
