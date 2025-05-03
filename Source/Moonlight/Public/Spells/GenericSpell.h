// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GenericSpell.generated.h"

UCLASS(Blueprintable)
class MOONLIGHT_API UGenericSpell : public UObject
{
	GENERATED_BODY()

public:
	UGenericSpell();

	virtual void ExecuteSpell(TMap<FName, UObject*>& Params) PURE_VIRTUAL(UGenericSpell::ExecuteSpell, );

protected:
	const float TICK = 0.001f;
	//Time in Seconds
	UPROPERTY(EditAnywhere, Category = Specs)
	float Cooldown = 2.0f;
	//Charges
	UPROPERTY(EditAnywhere, Category = Specs)
	int32 Charges = 2;

	FTimerHandle CooldownTimer;
	float RemainingCooldown;
	int32 RemainingCharges;

	void AddChargeToSpell();
	void RemoveChargeToSpell();


#pragma region GET/SET
public:
	FORCEINLINE float GetRemainingCooldown() { return RemainingCooldown; }
	FORCEINLINE int32 GetRemainingChargesn() { return RemainingCharges; }
	FORCEINLINE float GetCooldown() { return Cooldown; }
	FORCEINLINE int32 GetgChargesn() { return Charges; }
	FORCEINLINE void SetCooldown(float NewCooldown) { Cooldown = NewCooldown; }
	FORCEINLINE void SetCharges(int32 NewCharges) { Charges = NewCharges; }
#pragma endregion
};
