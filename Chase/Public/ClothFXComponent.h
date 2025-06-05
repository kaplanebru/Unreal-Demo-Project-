

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClothFXComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHASE_API UClothFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UClothFXComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth")
	UStaticMeshComponent* ClothMesh;
	
	UFUNCTION()
	void DestroyCloth();

	UFUNCTION(BlueprintCallable)
	void SetClothMesh(UStaticMeshComponent* NewClothMesh);

};
