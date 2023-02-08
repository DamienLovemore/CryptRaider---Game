// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Type of component and *, mean that it is a pointer to that component type.
	//GetOwner gets the reference to the component that owns this mover actor component.
	AActor* owner = this->GetOwner(); 

	// --Pointers e GetOwner()--
	//%u is to format unsigned integers.(Memory positions are stored in integers)
	UE_LOG(LogTemp, Display, TEXT("The memory address of the owner of the mover component is: {%u}"), owner);
}

