// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MovementDataComponent.h"
#include "UObject/ConstructorHelpers.h"

UMovementDataComponent::UMovementDataComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;

	MovementState = EMovementState::Idle;
}


