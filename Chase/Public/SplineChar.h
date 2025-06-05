

#pragma once

#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "IntroCharAnimInstance.h"
#include "SplinePathActor.h"
#include "GameFramework/Actor.h"
#include "SplineChar.generated.h"

UCLASS()
class CHASE_API ASplineChar : public AActor
{
	GENERATED_BODY()
	
public:	
	ASplineChar();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UChildActorComponent* ChildActorComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	ASplinePathActor* SplinePath;

	float MovementProgress = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	float MovementSpeed = 100.0f; // cm per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	FRotator RotationOffset = FRotator(0.0f, -90.0f, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	USceneComponent* PlayerHolder;

	
	UFUNCTION(BlueprintCallable)
	void TriggerSplineMotion();

	UFUNCTION()
	void FollowSpline(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void TriggerSequenceAnimation();


private:
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY()
	USkeletalMeshComponent* Mesh;

	UPROPERTY()
	UIntroCharAnimInstance* AnimInstance;
	
	UPROPERTY()
	bool bIsMoving = false;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void SetMeshAndAnimation();
};
