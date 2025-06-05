


#include "ClothFX.h"

#include "IntroEventbus.h"

// Sets default values
AClothFX::AClothFX()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AClothFX::BeginPlay()
{
	Super::BeginPlay();
	IntroEventbus::OnEndOfSpline.AddUObject(this, &AClothFX::DestroyCloth);
	
}

void AClothFX::DestroyCloth()
{
	// if (IsValid(ClothMesh))
	// {
	// 	ClothMesh->DestroyComponent();
	// 	//Destroy();
	// }
	
}



