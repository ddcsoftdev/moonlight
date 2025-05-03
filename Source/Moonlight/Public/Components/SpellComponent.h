// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spells/GenericSpell.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Moonlight), meta = (BlueprintSpawnableComponent))
class MOONLIGHT_API USpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USpellComponent();

	UGenericSpell* GetSpell(TSubclassOf<UGenericSpell> Class) const;
	int32 RemoveSpell(TSubclassOf<UGenericSpell> Class);
	void AddSpell(TSubclassOf <UGenericSpell> Class);

protected:
	void InitializeSpells();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spells)
	TArray< TSubclassOf<UGenericSpell>> Spells;

	TMap<TSubclassOf<UGenericSpell>, UGenericSpell*> ConstructedSpells;

private:
	UGenericSpell* CreateSpellInstance(TSubclassOf<UGenericSpell> Class);
#pragma region GET/SET
public:

#pragma endregion
};
