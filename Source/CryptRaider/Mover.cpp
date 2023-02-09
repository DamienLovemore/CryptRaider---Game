// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

//All the math helper functions of Unreal like:
//Round, Abs, Clamp and so on.
#include "Math/UnrealMathUtility.h"

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

	this->OriginalLocation = this->GetOwner()->GetActorLocation();	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->ShouldMove)
	{
		FVector CurrentLocation = this->GetOwner()->GetActorLocation();
		FVector TargetLocation = this->OriginalLocation + this->MoveOffset;
		//Calculates the speed based on the distance between the start and end locations,
		//and the move time value.
		float speed = FVector::Distance(OriginalLocation, TargetLocation) / this->MoveTime;

		//Calculates where it should be in this frame, until it reaches its destination
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, speed);
		//Moves to the calculated new location
		this->GetOwner()->SetActorLocation(NewLocation);
	}	
	
	// //Type of component and *, mean that it is a pointer to that component type.
	// //GetOwner gets the reference to the component that owns this mover actor component.
	// AActor* Owner = this->GetOwner();
	// //(*Owner). or Owner-> does the same thing, but it is more readable to use
	// //-> for pointers, and * for structs like FString
	// FString Name = Owner->GetActorNameOrLabel();
	// //ToCompactString returns a string representation of the vector
	// FString Location = Owner->GetActorLocation().ToCompactString();

	// //*Name converts the FString into a actual string also.
	// UE_LOG(LogTemp, Display, TEXT("Mover Owner:  %s"), *Name);
	// UE_LOG(LogTemp, Display, TEXT("Mover Owner Location: %s"), *Location);


	// --Pointers e GetOwner()--
	//%u is to format unsigned integers.(Memory positions are stored in integers)
	//UE_LOG(LogTemp, Display, TEXT("The memory address of the owner of the mover component is: {%u}"), owner);

	//Deferencing pointers
	// float MyFloat = 5;
	// float* YourFloat = &MyFloat;
	// float FloatValue = *YourFloat;
	// UE_LOG(LogTemp, Display, TEXT("YourFloat Value: %f"), FloatValue);
}
