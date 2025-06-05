


#include "Torso.h"



ATorso::ATorso()
{
	PrimaryActorTick.bCanEverTick = false;
	CreateSlots();
}

void ATorso::BeginPlay()
{
	Super::BeginPlay();
	
}

FTransform  ATorso::PlaceBodyPart(AActor* OtherActor)
{
	CurrentBodyPart = Cast<ABodyPart>(OtherActor);
	if (!IsValid(CurrentBodyPart))
	{
		UE_LOG(LogTemp, Warning, TEXT("BodyPart is invalid"));
		return FTransform::Identity;
	}
	CollectedBodyParts.Add(CurrentBodyPart);
	CurrentBodyPart->SetActorEnableCollision(false);
	CurrentBodyPart->BePlaced();
	//CurrentBodyPart->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//CurrentBodyPart->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform); //KeepRelativeTransform
	
	USceneComponent* slot = BodySlots[CurrentBodyPart->Type];
	auto tempTransform = slot->GetComponentTransform();
	tempTransform.SetScale3D(CurrentBodyPart->GetActorScale());
	return tempTransform;//slot->GetComponentTransform();//GetRelativeTransform();//GetComponentTransform();
}

bool ATorso::HasPhysicalIntegrity()
{
	return CollectedBodyParts.Num() == BodySlots.Num();
	//if true send event
}

ABodyPart* ATorso::GetCurrentBodyPart()
{
	if (!IsValid(CurrentBodyPart))
	{
		UE_LOG(LogTemp, Warning, TEXT("BodyPart is invalid"));
		return nullptr;
	}
	return CurrentBodyPart;
}


void ATorso::CreateSlots()
{
	TorsoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoMesh"));
	RootComponent = TorsoMesh; // Or attach to another root
	
	UEnum* Enum = StaticEnum<EBodyPart>();
	if (!Enum)
	{
		UE_LOG(LogTemp, Error, TEXT("Enum not found!"));
		return;
	}

	for (int32 i = 0; i < Enum->NumEnums() - 1; i++) // Exclude the 'MAX' enum value at the end
	{
		EBodyPart BodyType = (EBodyPart)Enum->GetValueByIndex(i);
		FString BodyPartName = Enum->GetNameStringByIndex(i);

		BodySlots.Add(BodyType, CreateDefaultSubobject<USceneComponent>(*BodyPartName));
		BodySlots[BodyType]->SetupAttachment(RootComponent);
	}
}



