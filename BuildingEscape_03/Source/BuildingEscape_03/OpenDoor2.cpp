// Evan VanOsdol 2017

#include "BuildingEscape_03.h"
#include "OpenDoor2.h"


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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		UOpenDoor();
	}
}

void UOpenDoor2::UOpenDoor()
{
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);

	Owner->SetActorRotation(NewRotation);
}


