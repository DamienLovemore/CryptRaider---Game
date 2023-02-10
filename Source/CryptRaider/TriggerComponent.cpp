// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();	

    UE_LOG(LogTemp, Display, TEXT("Something"));
}