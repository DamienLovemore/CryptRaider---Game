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

	// ...
	
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

	//The player camera current location
	FVector Start = this->GetComponentLocation();
	//Gets the forward direction of the camera
	//(Where the player is currently looking)
	FVector End = Start + (this->GetForwardVector() * this->MaxGrabDistance);
	DrawDebugLine(this->GetWorld(), Start, End, FColor::FromHex("#f7afba"));
}

