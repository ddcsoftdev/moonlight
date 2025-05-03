// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Spells/GenericSpell.h"
#include "DashSpell.generated.h"

class AMCharacter;
UCLASS(Blueprintable)
class MOONLIGHT_API UDashSpell : public UGenericSpell
{
	GENERATED_BODY()

public:
	UDashSpell();

	virtual void ExecuteSpell(TMap<FName, UObject*>& Params) override;

	UPROPERTY(EditAnywhere, Category = Specs)
	float LaunchDistance = 2500.0f;

private:
	void LaunchDash(AMCharacter* Character);
};
