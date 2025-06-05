

#pragma once

#include "Kismet/GameplayStatics.h"  // For UGameplayStatics
#include "GameFramework/Character.h"  // For ACharacter class
#include "Camera/CameraComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MuralPool.h"
#include "CoreMinimal.h"
#include "ISelectable.h"
#include "Components/ActorComponent.h"
#include "Selector.generated.h"


UENUM(BlueprintType)
enum class SelectionState : uint8
{
	Passive   UMETA(DisplayName = "None"),
	InDetection   UMETA(DisplayName = "InDetection"),
	Grabbing  UMETA(DisplayName = "Grabbing"),
};

class UCameraComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShowSelectionUI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideSelectionUI);


//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)

class MARCUS_MANSION_API USelector : public UActorComponent
{
	GENERATED_BODY()

public:	
	USelector();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintAssignable, Category = "Selector")
	FOnShowSelectionUI OnShowSelectionUI;

	UPROPERTY(BlueprintAssignable, Category = "Selector")
	FOnHideSelectionUI OnHideSelectionUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selector")
	SelectionState SelectionState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectionData")
	float SelectionDistance = 3000.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Selector")
	void SendRayForDetection();

	UFUNCTION(BlueprintCallable, Category = "Selector")
	void UserGrabRequest();

	UFUNCTION(BlueprintCallable, Category = "Selector")
	void UserReleaseRequest();
	
	UFUNCTION(BlueprintCallable, Category = "Selector")
	void GrabSelection(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Selector")
	void OnTick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Selector")
	void Equip();
	
	UFUNCTION(BlueprintCallable, Category = "Selector")
	void UnEquip();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grabbing")
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY()
	bool bIsDtected = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabbing")
	float GrabDistance = 170;

	
	TArray<ISelectable*> Selectables;

	// UPROPERTY()
	// TScriptInterface<ISelectable> Selectable;

	UMuralPool* MuralPool;


private:
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	ACharacter* PlayerCharacter;

	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	UPrimitiveComponent* HitComponent;

	UPROPERTY()
	FVector CameraLocation;
	UPROPERTY()
	FRotator CameraRotation;

	UFUNCTION()
	void Setup();

	UFUNCTION()
	void ShowDetection();

	UFUNCTION()
	void HideDetection();

	UPROPERTY()
	bool bFoundSelectable = false;

	UFUNCTION()
	void StopSelectingTheCurrentSelection();
		
};

