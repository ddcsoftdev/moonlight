// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/EMovementState.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementDataComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Moonlight), meta = (BlueprintSpawnableComponent))
class MOONLIGHT_API UMovementDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMovementDataComponent();

#pragma region CORE_DATA
protected:
	EMovementState MovementState;
	float WalkingSpeedModifier = 1.0f;

	UPROPERTY(EditAnywhere, Category = Data)
	float WalkingSpeed = 500.0f;

#pragma endregion CORE_DATA

#pragma region GET/SET
public:
	FORCEINLINE float GetWalkingSpeed() const { return WalkingSpeed * WalkingSpeedModifier; }
	FORCEINLINE EMovementState GetMovementState() const { return MovementState; }
	FORCEINLINE void SetWalkingSpeedModifier(float Speed) { WalkingSpeedModifier = Speed; }
#pragma endregion
};
