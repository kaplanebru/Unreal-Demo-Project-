#include "Selector.h"

#include "CommonEventbus.h"
#include "ISelectable.h"

ISelectable* Selectable;

USelector::USelector()
{
	PrimaryComponentTick.bCanEverTick = false;
	Selectables.Empty();
	Selectable = nullptr;

	AActor* OwnerActor = GetOwner();
	if (!OwnerActor) return;
	MuralPool = OwnerActor->FindComponentByClass<UMuralPool>();
}


void USelector::BeginPlay()
{
	Super::BeginPlay();
	Setup();
	SelectionState = SelectionState::InDetection;

	CommonEventbus::OnPlaceObjectRequest.BindUObject(this, &USelector::StopSelectingTheCurrentSelection);
}

void USelector::OnTick(float DeltaTime)
{
	if (SelectionState == SelectionState::InDetection)
		SendRayForDetection();
	else if (SelectionState == SelectionState::Grabbing)
		GrabSelection(DeltaTime);
}

void USelector::Equip()
{
	if (SelectionState == SelectionState::Grabbing && Selectable)
	{
		Selectable->Hide();
		Selectables.Add(Selectable);
		bIsDtected = false;
		SelectionState = SelectionState::InDetection;
	}
}

void USelector::UnEquip()
{
	if (Selectables.Num()>0) //SelectionState != SelectionState::Grabbing && 
	{
		Selectable = Selectables.Last();
		Selectable->Show();
		Selectables.Remove(Selectable);
		bIsDtected = true;
		UserGrabRequest();
	}
}

void USelector::Setup()
{
	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Camera = PlayerCharacter->FindComponentByClass<UCameraComponent>();

	if (!PlayerCharacter) return;
	PhysicsHandle = PlayerCharacter->FindComponentByClass<UPhysicsHandleComponent>();
}

FHitResult Hit;
void USelector::SendRayForDetection()
{
	if (!PlayerController) return;

	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector Start = CameraLocation;
	FVector End = Start + (CameraRotation.Vector() * SelectionDistance);
	
	if (!GetOwner()) return;
	FCollisionQueryParams TraceParams(FName(TEXT("RaycastTrace")), true, GetOwner());

	FCollisionObjectQueryParams ObjectTypes;
	ObjectTypes.AddObjectTypesToQuery(ECC_WorldDynamic);

	if (!PlayerCharacter) return;
	TraceParams.AddIgnoredActor(PlayerCharacter);

	bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectTypes, TraceParams);

	if (bHit)
	{
		if (Hit.GetActor() && Hit.GetActor()->Implements<USelectable>())
		{
			Selectable = Cast<ISelectable>(Hit.GetActor());
			if (Selectable)
			{
				//bIsDtected = true;
				ShowDetection();
				bFoundSelectable = true;
			}
		}
		else
		{
			//bIsDtected = false;
			Selectable = nullptr;
			HideDetection();
		}
	}
}


void USelector::ShowDetection()
{
	if (bIsDtected) return;
	bIsDtected = true;

	if (OnShowSelectionUI.IsBound())
		OnShowSelectionUI.Broadcast();
	
	// DrawDebugPoint(
	// 	GetWorld(),
	// 	Hit.ImpactPoint,
	// 	10.0f, // Size of the point
	// 	FColor::Cyan,
	// 	false, // bPersistentLines
	// 	-1.0f // Lifetime in seconds
	// );
}

void USelector::HideDetection()
{
	if (!bIsDtected) return;
	bIsDtected = false;

	if (OnHideSelectionUI.IsBound())
		OnHideSelectionUI.Broadcast();
	
}

void USelector::StopSelectingTheCurrentSelection()
{
	bIsDtected = false;
	SelectionState = SelectionState::InDetection;
	//SelectionState = SelectionState::Passive;
	//Selectable = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("StopSelectingTheCurrentSelection"));
}


void USelector::UserReleaseRequest()
{
	if (SelectionState == SelectionState::Grabbing)
	{
		SelectionState = SelectionState::InDetection;
		bIsDtected = false;
		Selectable->Fall();
		Selectable = nullptr;
	}
}

void USelector::UserGrabRequest()
{
	if (!bIsDtected) return;
	if (!Selectable) return;
	SelectionState = SelectionState::Grabbing;
	bIsDtected = false;
	Selectable->ExecuteSelection(Hit);
}


void USelector::GrabSelection(float DeltaTime) //TScriptInterface<ISelectable> Selectable
{
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector TargetLocation = CameraLocation + CameraRotation.Vector() * GrabDistance;
	FVector CurrentLocation = Selectable->GetWorldLocation();


	float Distance = FVector::Dist(CurrentLocation, TargetLocation);
	float InterpSpeed = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 500.f), FVector2D(20.f, 10.f), Distance);
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);

	FRotator CurrentRotation = Selectable->GetWorldRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, CameraRotation, DeltaTime, InterpSpeed);
	// 20.f is interpolation speed

	Selectable->SetWorldLocation(NewLocation);
	Selectable->SetWorldRotation(CameraRotation);
}
