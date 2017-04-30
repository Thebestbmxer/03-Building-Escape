// Evan VanOsdol 2017

#include "BuildingEscape_03.h"
#include "OpenDoor2.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor2::UOpenDoor2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor2::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Pressure Pleate"), *GetOwner()->GetName())
	}
}

// Called every frame
void UOpenDoor2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnPlate() > 30.f) // TODO make into a parameter
	{
		UOpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		UCloseDoor();
	}
}

float UOpenDoor2::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;

	//Find all the overlaping actors
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) { return TotalMass; }	// If Pressure Plate is not working
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor-> GetName())
	}
	return TotalMass;
}

void UOpenDoor2::UOpenDoor()
{
	if (!Owner) { return; }	// If Owner is not working
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor2::UCloseDoor()
{
	if (!Owner) { return; }	// If Owner is not working
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}
