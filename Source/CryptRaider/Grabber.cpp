// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
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

	UPhysicsHandleComponent *PhysicsHandler = this->GetPhysicsHandle();
	if (PhysicsHandler == nullptr)
		return;

	//If we are not holding anything, them does not
	if (PhysicsHandler->GetGrabbedComponent() != nullptr)
	{
		//As we move around when we are grabbing a object, moves it with us and rotates it according to
		//the camera rotation
		FVector TargetLocation = this->GetComponentLocation() + (this->GetForwardVector() * this->HoldDist);
		PhysicsHandler->SetTargetLocationAndRotation(TargetLocation, this->GetComponentRotation());
	}	
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
	UPhysicsHandleComponent *PhysicsHandler = this->GetPhysicsHandle();
	// If there is not a PhysicsHandler them it should quit the function
	//(It is necessary for grabing objects)
	if (PhysicsHandler == nullptr)
		return;

	// The player camera current location
	FVector Start = this->GetComponentLocation();
	// Gets the forward direction of the camera
	//(Where the player is currently looking)
	FVector End = Start + (this->GetForwardVector() * this->MaxGrabDistance);
	// Draws a line visible only in editor with F8
	// for debug purposes
	DrawDebugLine(this->GetWorld(), Start, End, FColor::FromHex("#f7afba"));
	// Draws a sphere in the max distance that it can reach in the direction
	// it is looking
	// DrawDebugSphere(this->GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	// The shape to be used in the Sweep trace
	FCollisionShape Sphere = FCollisionShape::MakeSphere(this->GrabRadius);
	// Stores the hit result of Sweep trace function
	FHitResult HitResult;
	// Detect the first collision, using a shape instead of a straight line, and with
	// that specific trace channel.
	// FQuat::Identity means no rotation
	// It returns true if it has hitted anything, the information about the things it hitted
	// is stored in the first variable
	bool HasHit = this->GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

	if (HasHit)
	{		
		UPrimitiveComponent *TargetObject = HitResult.GetComponent();
		//When a object that has simulate physics is still for too long, it disables its
		//simulate physics. So we must make sure to enable it when grabbing it
		TargetObject->WakeAllRigidBodies();

		DrawDebugSphere(this->GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::FromHex("#9b4a75"), false, 5);
		
		// When working with name if you do not want to pass anything you use NAME_None
		// There is a same function but that does not rotate when grabbing, it is called
		// GrabComponentAtLocation
		PhysicsHandler->GrabComponentAtLocationWithRotation(TargetObject, NAME_None, HitResult.ImpactPoint, this->GetComponentRotation());
	}
}

void UGrabber::Release()
{
	//Verifies if we have a PhysicsHandler to grab and release things
	UPhysicsHandleComponent *PhysicsHandler = this->GetPhysicsHandle();
	if (PhysicsHandler == nullptr)
		return;

	UPrimitiveComponent* GrabedObject = PhysicsHandler->GetGrabbedComponent();
	//Check if we are holding something
	if(GrabedObject != nullptr)
	{
		//If we have grabed it for a while and not released it, its
		//simulate physics could have got into sleep mode, so we wake it
		GrabedObject->WakeAllRigidBodies();
		//Drops the component that we are holding
		PhysicsHandler->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent *PhysicsHandler = this->GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandler == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	
	return PhysicsHandler;
}