// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UArmorComponent;

UCLASS(Blueprintable, ClassGroup = (Moonlight), meta = (BlueprintSpawnableComponent))
class MOONLIGHT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MoonlightComponents, meta = (AllowPrivateAccess = "true"))
	UArmorComponent* ArmorComponent;

#pragma region GET/SET
public:
	FORCEINLINE class UArmorComponent* GetArmorComponent() const { return ArmorComponent; }
#pragma endregion
};
