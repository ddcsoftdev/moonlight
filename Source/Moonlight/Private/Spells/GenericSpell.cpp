// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/GenericSpell.h"
#include "UObject/ConstructorHelpers.h"


UGenericSpell::UGenericSpell()
{
	RemainingCooldown = 0.0f;
	RemainingCharges = Charges;
	CooldownTimer = FTimerHandle();
}

void UGenericSpell::AddChargeToSpell()
{
	int32 Current = RemainingCharges + 1;
	RemainingCharges = Current > Charges ? Charges : Current;
}

void UGenericSpell::RemoveChargeToSpell()
{
	int32 Current = RemainingCharges - 1;
	RemainingCharges = Current < 0 ? 0 : Current;
}


