// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputStateComponent.h"
#include "UObject/ConstructorHelpers.h"


UInputStateComponent::UInputStateComponent()
{
	Inputs = TMap<const UInputAction*, FInputState>();
}

UInputStateComponent::UInputStateComponent(TArray<const UInputAction*> Mappings)
{
	UInputStateComponent();
	for (const UInputAction* Mapping : Mappings)
	{
		AddInput(Mapping);
	}
}



