// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	//How far it should check for grabable objects (In cm)
	float MaxGrabDistance = 400;

	UPROPERTY(EditAnywhere)
	//How big is the sphere used to detect collision in our sweep trace
	float GrabRadius = 100;

	// //Normal Ref you can change the original value of it.
	// //But Const Ref you cannot change the original value of it
	// void PrintDamage(const float& Damage);
	// //If you see a function that have a Reference but it is
	// //not a const, you can pretty much assure that it is a
	// //out parameter.
	// bool HasDamage(float& OutDamage);
};
