// Copyright Munero 2018

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

private: 
	/// how far ahead to reach 
	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach 
	void Grab();

	// When grab is released 
	void Release();

	//find attached phyics handle 
	void FindPhysicsHandleComponent();
	
	//setup (assumed) attached input component 
	void SetupInputComponent();

	// Return hit for first physics body in reach 
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Returns currents start of reach line
	FVector GetReachLineStart() const;

	//Returns current end of reach line
	FVector GetReachLineEnd() const;

};
