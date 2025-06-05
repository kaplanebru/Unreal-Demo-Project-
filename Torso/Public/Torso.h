

#pragma once

#include "UObject/EnumProperty.h"
#include "Enums.h"
#include "CoreMinimal.h"
#include "BodyPart.h"
#include "GameFramework/Actor.h"
#include "Torso.generated.h"




UCLASS(Blueprintable)
class TORSO_API ATorso : public AActor
{
	GENERATED_BODY()
	
public:	
	ATorso();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Torso")
	TMap<EBodyPart, USceneComponent*> BodySlots;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Torso")
	UStaticMeshComponent* TorsoMesh;

	

	UFUNCTION(BlueprintCallable)
	FTransform  PlaceBodyPart(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	bool HasPhysicalIntegrity();

	UFUNCTION(BlueprintCallable)
	ABodyPart* GetCurrentBodyPart();

	UFUNCTION()
	void CreateSlots();


private:
	UPROPERTY()
	ABodyPart* CurrentBodyPart;
	
	UPROPERTY()
	TArray<ABodyPart*> CollectedBodyParts;

};
