


#include "SpawnerComponent.h"

#include "IntroEventbus.h"

USpawnerComponent::USpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USpawnerComponent::SpawnToNewLocation(AActor* OtherActor)
{
	if (!IsValid(OtherActor)) return;
	
	ActorToSpawn = OtherActor;

	ActorToSpawn->SetActorEnableCollision(false);
	DisableActorInput(ActorToSpawn);
	
	if (!IsValid(ActorToSpawn)) return;
	
	if (bHasFXBefore)
	{
		PlayEffect();
		DelaySpawning();
	}
	else
	{
		Spawn();
	}
}

void USpawnerComponent::PlayEffect()
{
	
}

void USpawnerComponent::DelaySpawning()
{
	GetWorld()->GetTimerManager().SetTimer(
		DelayTimerHandle,
		this,
		&USpawnerComponent::Spawn,
		EffectDelay,
		false
	);
}

void USpawnerComponent::Spawn()
{
	if (IntroEventbus::OnEndOfSpline.IsBound())
		IntroEventbus::OnEndOfSpline.Broadcast();
	
	ActorToSpawn->SetActorLocationAndRotation(SpawnLocation, SpawnRotation, false, nullptr, ETeleportType::TeleportPhysics);
	ActorToSpawn->SetActorEnableCollision(true);
	EnableActorInput(ActorToSpawn);
}

void USpawnerComponent::EnableActorInput(AActor* Actor)
{
	APawn* Pawn = Cast<APawn>(Actor);
	if (Pawn)
	{
		Controller = Cast<APlayerController>(Pawn->GetController());
		if (Controller)
		{
			Pawn->EnableInput(Controller);
		}
	}
}

void USpawnerComponent::DisableActorInput(AActor* Actor)
{
	APawn* Pawn = Cast<APawn>(Actor);
	if (Pawn)
	{
		Controller = Cast<APlayerController>(Pawn->GetController());
		if (Controller)
		{
			Pawn->DisableInput(Controller);
		}
	}
}


