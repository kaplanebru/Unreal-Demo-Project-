


#include "ClothFXComponent.h"

#include "IntroEventbus.h"

// Sets default values for this component's properties
UClothFXComponent::UClothFXComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;
	IntroEventbus::OnEndOfSpline.AddUObject(this, &UClothFXComponent::DestroyCloth);

}


void UClothFXComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UClothFXComponent::SetClothMesh(UStaticMeshComponent* NewClothMesh)
{
	ClothMesh = NewClothMesh;
}


void UClothFXComponent::DestroyCloth()
{
	if (IsValid(ClothMesh))
	{
		ClothMesh->DestroyComponent();
	}
}

