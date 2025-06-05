#include "Corpse.h"
#include "PosessionEventbus.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
//#include "Runtime/Datasmith/DatasmithCore/Public/DatasmithDefinitions.h"


ACorpse::ACorpse()
{
	PrimaryActorTick.bCanEverTick = false;

	Setup();
}

void ACorpse::BeginPlay()
{
	Super::BeginPlay();
	SetCamPosition();

	SkeletalMesh = GetSkeletalMeshComponent(this);
	if (IsValid(SkeletalMesh))
	{
		FString MeshName = GetName();
		UE_LOG(LogTemp, Warning, TEXT("has SKELETAL MESH: %s"), *MeshName);
		AnimInstance = SkeletalMesh->GetAnimInstance();
		if (IsValid(AnimInstance))
		{
			CorpseAnimInstance = Cast<UCorpseAnimInstance>(AnimInstance);
			
			SetAnimationStartState();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no SKELETAL MESH"));
	}
}

void ACorpse::SetCamPosition()
{
	CamPosition = CamPositionIndicator->GetComponentLocation();
}

void ACorpse::Setup()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	CamPositionIndicator = CreateDefaultSubobject<USceneComponent>(TEXT("CamPositionIndicator"));
	CamPositionIndicator->SetupAttachment(RootScene); // Not replacing ro
}

USkeletalMeshComponent* ACorpse::GetSkeletalMeshComponent(AActor* Actor)
{
	TArray<USkeletalMeshComponent*> SkeletalMeshComps;
	Actor->GetComponents(SkeletalMeshComps, true); // `true` = recursive search

	if (SkeletalMeshComps.Num() > 0)
	{
		return SkeletalMeshComps[0]; // Return first found
	}
	return nullptr; // Not found
}

void ACorpse::SetAnimationStartState()
{
	if (CorpseAnimInstance)
	{
		CorpseAnimInstance->bIsInCorpseState = IsCorpse;
		//CorpseAnimInstance->bIsDying = !IsCorpse;
		
	}
}

ACorpse* ACorpse::NotifyContact()
{
	PosessionEventbus::OnContactWithCorpse().Broadcast(this);
	return this;
}


void ACorpse::ShowVisionLevel()
{
	if (ControlData->VisionLevel.IsNone())
		return;
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	
	UGameplayStatics::LoadStreamLevel(this, ControlData->VisionLevel, true, true, LatentInfo);
	//UE_LOG(LogTemp, Warning, TEXT("Show level: %s"), *ControlData->VisionLevel.ToString());
}

void ACorpse::HideVisionLevel()
{
	if (ControlData->VisionLevel.IsNone())
		return;
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	
	UGameplayStatics::UnloadStreamLevel(this, ControlData->VisionLevel, LatentInfo, true);
}

