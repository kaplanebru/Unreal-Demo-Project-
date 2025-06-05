#include "SplineChar.h"


ASplineChar::ASplineChar()
{
	PrimaryActorTick.bCanEverTick = true;
	Initialize();
}

void ASplineChar::BeginPlay()
{
	Super::BeginPlay();
	SetMeshAndAnimation();
}

void ASplineChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FollowSpline(DeltaTime); //test
}

void ASplineChar::TriggerSplineMotion()
{
	 if (!IsValid(AnimInstance)) return;
	 //AnimInstance->SetAnimState(EIntroCharAnimStates::Moving);

	bIsMoving = true;
}

void ASplineChar::FollowSpline(float DeltaTime)
{
	if (!bIsMoving) return;
	if (!SplinePath) return;

	MovementProgress += MovementSpeed * DeltaTime;

	float SplineLength = SplinePath->SplineComp->GetSplineLength();
	float Distance = FMath::Clamp(MovementProgress, 0.0f, SplineLength);

	FVector NewLocation = SplinePath->SplineComp->GetLocationAtDistanceAlongSpline(
		Distance, ESplineCoordinateSpace::World);
	FRotator NewRotation = SplinePath->SplineComp->GetRotationAtDistanceAlongSpline(
		Distance, ESplineCoordinateSpace::World);

	NewRotation += RotationOffset;
	SetActorLocation(NewLocation);
	SetActorRotation(NewRotation);
}

void ASplineChar::TriggerSequenceAnimation()
{
	AnimInstance->SetAnimState(EIntroCharAnimStates::Idle2);
}


void ASplineChar::Initialize()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	PlayerHolder = CreateDefaultSubobject<USceneComponent>("Player Holder");
	PlayerHolder->SetupAttachment(Root);
}

void ASplineChar::SetMeshAndAnimation()
{
	ChildActorComp = FindComponentByClass<UChildActorComponent>();
	if (ChildActorComp && ChildActorComp->GetChildActor())
	{
		UE_LOG(LogTemp, Error, TEXT("has child component"));

		AActor* ChildActor = ChildActorComp->GetChildActor();
		Mesh = ChildActor->FindComponentByClass<USkeletalMeshComponent>();
		if (Mesh)
		{
			UE_LOG(LogTemp, Error, TEXT("Found SkeletalMeshComponent"));

			AnimInstance = Cast<UIntroCharAnimInstance>(Mesh->GetAnimInstance());
			if (AnimInstance)
			{
				AnimInstance->SetAnimState(EIntroCharAnimStates::Idle1);
				UE_LOG(LogTemp, Error, TEXT("Found ANIM INSTANCE: From existing mesh"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not cast AnimInstance to UIntroCharAnimInstance"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No SkeletalMeshComponent found on ChildActor"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("no child component"));
	}

	// Mesh = FindComponentByClass<USkeletalMeshComponent>();
	// if (IsValid(Mesh))
	// {
	// 	AnimInstance = Cast<UIntroCharAnimInstance>(Mesh->GetAnimInstance());
	// 	if (IsValid(AnimInstance))
	// 	{
	// 		AnimInstance->SetAnimState(EIntroCharAnimStates::Idle1);
	// 		UE_LOG(LogTemp, Error, TEXT("find ANIM INSTANCE: From existing mesh"));
	// 	}
	// }
}
