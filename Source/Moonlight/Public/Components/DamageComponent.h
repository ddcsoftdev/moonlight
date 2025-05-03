// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Moonlight), meta = (BlueprintSpawnableComponent))
class MOONLIGHT_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageComponent();

};
