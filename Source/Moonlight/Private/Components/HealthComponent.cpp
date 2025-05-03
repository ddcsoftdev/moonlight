// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/ArmorComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	
	ArmorComponent = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComponent"));
}


