// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpellComponent.h"
#include "UObject/ConstructorHelpers.h"

USpellComponent::USpellComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;

	Spells = TArray <TSubclassOf<UGenericSpell>>();
	ConstructedSpells = TMap <TSubclassOf<UGenericSpell>, UGenericSpell*>();
}

void USpellComponent::InitializeSpells()
{
	for (TSubclassOf<UGenericSpell> SpellClass : Spells)
	{
		AddSpell(SpellClass);
	}
}

void USpellComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeSpells();
}

UGenericSpell* USpellComponent::CreateSpellInstance(TSubclassOf<UGenericSpell> Class)
{
    return NewObject<UGenericSpell>(this, Class);
}

UGenericSpell* USpellComponent::GetSpell(TSubclassOf<UGenericSpell> Class) const
{
    for (const auto& Pair : ConstructedSpells)
    {
        if (Pair.Key->IsChildOf(Class))
        {
            return Pair.Value;
        }
    }
    checkf(false, TEXT("No spell found for class %s"), *Class->GetName());
    return nullptr;
}

void USpellComponent::AddSpell(TSubclassOf <UGenericSpell> Class)
{ 
    RemoveSpell(Class);
    ConstructedSpells.Add(Class, CreateSpellInstance(Class)); 
}

int32 USpellComponent::RemoveSpell(TSubclassOf<UGenericSpell> Class)
{
    TArray<TSubclassOf<UGenericSpell>> KeysToRemove;

    for (const auto& Pair : ConstructedSpells)
    {
        if (Pair.Key->IsChildOf(Class))
        {
            KeysToRemove.Add(Pair.Key);
        }
    }

    int32 RemovedCount = 0;
    for (const auto& Key : KeysToRemove)
    {
        RemovedCount += ConstructedSpells.Remove(Key);
    }
    return RemovedCount;
}




