

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClothFX.generated.h"

UCLASS(Blueprintable)
class CHASE_API AClothFX : public AActor
{
	GENERATED_BODY()
	
public:	
	AClothFX();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth")
	UStaticMeshComponent* ClothMesh;
	
	UFUNCTION()
	void DestroyCloth();


};
