// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();	

    UE_LOG(LogTemp, Display, TEXT("Something"));
}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//An array of actors pointers
	TArray<AActor*> Actors;
	//Puts all the objects that are touching the collider
	//in the Actors variable.
	this->GetOverlappingActors(Actors);

	//If the counting of elements in the array is greater them
	//zero (not empty)
	if (Actors.Num() > 0)
	{		
		FString ObjectName = Actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("This overlapped the collider: {%s}"), *ObjectName);
	}
}