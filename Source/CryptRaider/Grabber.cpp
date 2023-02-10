// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Find a object from a specific type from that parent.
	//(In this case the thing that handles the physics for the game)
	UPhysicsHandleComponent* PhysicsHandler = this->GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//Prevents us from getting a null pointer value, and trying to use it.
	//(It would result in a crash)
	if (PhysicsHandler != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("The name of the component found: {%s}"), *PhysicsHandler->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// // --Logs the current camera rotation--
	// FRotator cameraRotation = this->GetComponentRotation();	
	// // FString rotationFormatted = cameraRotation.ToCompactString();
	// // UE_LOG(LogTemp, Display, TEXT("Camera rotation: {%s}"), *rotationFormatted);

	// // --Getting the world of this object--
	// //Gets the world (environment) in which the objects are contained
	// UWorld* World = this->GetWorld();

	// // --Time played by the player--
	// //The time in seconds which the game has been played
	// //(Is paused when it is paused, and is clamped)
	// float TimePlayed = World->TimeSeconds;
	// UE_LOG(LogTemp, Display, TEXT("You've played the game for: {%f} seconds"), TimePlayed);

	// // --Pointers and References--
	// float Damage;
	// if (this->HasDamage(Damage))
	// {
	// 	this->PrintDamage(Damage);
	// }
	// // float& DamageRef = Damage;
	// // DamageRef = 5;
	// //UE_LOG(LogTemp, Display, TEXT("DamageRef: %f, Damage: %f"), DamageRef, Damage);

	// // Const Refs and Out Parameters
	// //this->PrintDamage(Damage);
	// UE_LOG(LogTemp, Display, TEXT("Original Damage: %f"), Damage);
}

// void UGrabber::PrintDamage(const float& Damage)
// {
// 	UE_LOG(LogTemp, Display, TEXT("Damage: %f"), Damage);
// }

// //Receives the value, do some calculation and updates the
// //original value for the rest of the class
// bool UGrabber::HasDamage(float& OutDamage)
// {
// 	OutDamage = 5;
// 	return true;
// }

void UGrabber::Grab()
{
	//The player camera current location
	FVector Start = this->GetComponentLocation();
	//Gets the forward direction of the camera
	//(Where the player is currently looking)
	FVector End = Start + (this->GetForwardVector() * this->MaxGrabDistance);
	//Draws a line visible only in editor with F8
	//for debug purposes
	DrawDebugLine(this->GetWorld(), Start, End, FColor::FromHex("#f7afba"));

	//The shape to be used in the Sweep trace
	FCollisionShape Sphere = FCollisionShape::MakeSphere(this->GrabRadius);
	//Stores the hit result of Sweep trace function
	FHitResult HitResult;
	//Detect the first collision, using a shape instead of a straight line, and with
	//that specific trace channel.
	//FQuat::Identity means no rotation
	//It returns true if it has hitted anything, the information about the things it hitted
	//is stored in the first variable
	bool HasHit = this->GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

	if (HasHit)
	{
		AActor* HitActor = HitResult.GetActor();
		FString HittedObject = HitActor->GetName();
		UE_LOG(LogTemp, Display, TEXT("I've hitted on: {%s}"), *HittedObject);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released grabber"));
}