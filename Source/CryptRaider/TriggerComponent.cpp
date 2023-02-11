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

	

	//If the counting of elements in the array is greater them
	//zero (not empty)
	// if (Actors.Num() > 0)
	// {
	// 	//--Acessing TArray values--
	// 	FString ObjectName = Actors[0]->GetActorNameOrLabel();
	// 	UE_LOG(LogTemp, Display, TEXT("This overlapped the collider: {%s}"), *ObjectName);
	// }

	// --While loop implementation--
	// int32 index = 0;
	// while(index < Actors.Num())
	// {
	// 	FString ObjectName = Actors[index]->GetActorNameOrLabel();
	// 	UE_LOG(LogTemp, Display, TEXT("This overlapped the collider: {%s}"), *ObjectName);
	// 	index++;
	// }

	// --For loop implementation--
	// for (int32 i = 0; i < Actors.Num(); i++)
	// {
	// 	FString ObjectName = Actors[i]->GetActorNameOrLabel();
	// 	UE_LOG(LogTemp, Display, TEXT("This overlapped the collider: {%s}"), *ObjectName);
	// }

	AActor* ObjectFound = this->GetAcceptableActor();
	//Unlocks the door
	if (ObjectFound != nullptr)
	{
		//Gets the parent of the actor (its root)
		//Casting check if this USceneComponent is a UPrimitiveComponent, if it is
		//return a pointer to it. If not, them returns null
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(ObjectFound->GetRootComponent());
		if (Component != nullptr)
		{
			//Disables its physics so it does not bounce off the wall
			Component->SetSimulatePhysics(false);
		}		
		//Attach the valid object to this component (keeping its transform
		//and scales that was used in the world, and let it fixed with the object
		//not moving)
		Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

		this->Mover->SetShouldMove(true);
	}
	//Lock the door again
	else
	{
		this->Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	this->Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	//An array of actors pointers
	TArray<AActor*> Actors;
	//Puts all the objects that are touching the collider
	//in the Actors variable.
	this->GetOverlappingActors(Actors);

	// -For range implementation--
	for (AActor* Actor : Actors)
	{
		//If it has found return the one it found
		//Only accept valid object (with the Unlock tag), and that
		//it is not being held in the moment
		if ((Actor->ActorHasTag(this->UnlockTag)) && (!Actor->ActorHasTag("Grabbed")))
		{
			return Actor;
		}		
	}

	//If nothing was found returns null
	return nullptr;	
}