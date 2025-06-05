


#include "BodyPart.h"

#include "MovieSceneTracksComponentTypes.h"
#include "Marcus_Mansion/CommonEventbus.h"


ABodyPart::ABodyPart()
{
	PrimaryActorTick.bCanEverTick = false;
	Initiate();

}

void ABodyPart::BeginPlay()
{
	Super::BeginPlay();
	//TEMP:
	// PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// this->AttachToComponent(PlayerCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

}


void ABodyPart::SetWorldLocation(const FVector& NewLocation)
{
	SetActorLocation(NewLocation);
}

void ABodyPart::SetWorldRotation(const FRotator& NewRotation)
{
	SetActorRotation(NewRotation);
}

FVector ABodyPart::GetWorldLocation() const
{
	return GetActorLocation();
}

FRotator ABodyPart::GetWorldRotation() const
{
	return GetActorRotation();
}

void ABodyPart::SetCollision(bool Enable)
{
	if (Enable)
	{
		Trigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ABodyPart::Fall()
{
	if (Mesh)
	{
		Mesh->SetSimulatePhysics(true);
		Mesh->SetEnableGravity(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		// HitComponent->SetEnableGravity(false);
		// HitComponent->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
		// HitComponent->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}
}

void ABodyPart::Hide()
{
	SetActorHiddenInGame(true);
	Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABodyPart::Show()
{
	SetActorHiddenInGame(false);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABodyPart::BePlaced()
{
	
	if (CommonEventbus::OnPlaceObjectRequest.IsBound())
	{
		CommonEventbus::OnPlaceObjectRequest.Execute();
	}
}



void ABodyPart::ExecuteSelection(FHitResult& Hit)
{
	if (Mesh)
	{
		Mesh->SetSimulatePhysics(false);
		Mesh->SetEnableGravity(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


void ABodyPart::Initiate()
{
	//Root = CreateDefaultSubobject<USceneComponent>("Root");
	//RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	if (IsValid(Mesh))
	{
		//Mesh->SetupAttachment(RootComponent);
		RootComponent = Mesh;
	}
	else
	{
		return;
	}
	
	
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	if (IsValid(Trigger))
		Trigger->SetupAttachment(RootComponent);
}


