// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergyComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Moonlight), meta = (BlueprintSpawnableComponent))
class MOONLIGHT_API UEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnergyComponent();

};
