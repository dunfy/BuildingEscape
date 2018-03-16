// Copyright Munero 2018

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h" 

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (Owner == nullptr) { 
		UE_LOG(LogTemp, Error, TEXT("Owner missing from OpenDoor"));
	}

	if (PressurePlate == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *Owner->GetName());
	}
}

void UOpenDoor::OpenDoor()
{
	if (!Owner) { return; }
	//Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));

	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the trigger volume
	if (GetTotalMassOfActorsOnPlate() > 50.f) { // TODO Make into param 
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	} 
	
	//check if it's time to close the door 
	if(GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorClosedDelay) {
		CloseDoor();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding mass together 
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Error, TEXT("%s on pressure plate"), *Actor->GetName());
	}

	return TotalMass;
}
