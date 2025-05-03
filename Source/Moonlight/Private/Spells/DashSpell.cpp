// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/DashSpell.h"
#include "UObject/ConstructorHelpers.h"

#include "Characters/MCharacter.h"


UDashSpell::UDashSpell()
{

}

void UDashSpell::ExecuteSpell(TMap<FName, UObject*>& Params)
{
	if (RemainingCharges <= 0)
	{
		return;
	}
	if (AMCharacter* Character = Cast<AMCharacter>(*Params.Find(FName("Character"))))
	{
		if (UWorld* WorldRef = Character->GetWorld())
		{
			LaunchDash(Character);
			WorldRef->GetTimerManager().ClearTimer(CooldownTimer);
			WorldRef->GetTimerManager().SetTimer(CooldownTimer, [this, WorldRef]() 
				{ 
					RemainingCooldown += TICK;
					if (RemainingCooldown >= Cooldown) 
					{
						AddChargeToSpell();
						if (RemainingCharges == Charges)
						{
							WorldRef->GetTimerManager().ClearTimer(CooldownTimer);
						}
					}
				}, TICK, true);
		}
	}

}

void UDashSpell::LaunchDash(AMCharacter* Character)
{
	FVector LaunchDirection = Character->GetActorForwardVector();
	LaunchDirection.Z = 0.f;
	LaunchDirection.Normalize();
	FVector LaunchForce = LaunchDirection * LaunchDistance;

	Character->LaunchCharacter(LaunchForce, true, true);
	RemoveChargeToSpell();
}


