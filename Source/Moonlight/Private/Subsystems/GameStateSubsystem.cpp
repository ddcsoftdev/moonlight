// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GameStateSubsystem.h"
#include "UObject/ConstructorHelpers.h"



UGameStateSubsystem::UGameStateSubsystem()
{
}

void UGameStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("GameStateSubsystem Initialized"));
	SetGameState(EGameState::Initializing);
}

void UGameStateSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("GameStateSubsystem Deinitialized"));
	SetGameState(EGameState::ShuttingDown);

	Super::Deinitialize();
}

UGameStateSubsystem* UGameStateSubsystem::Get(const UObject* WorldContextObject)
{
    if (!WorldContextObject)
    {
        UE_LOG(LogTemp, Warning, TEXT("UGameStateSubsystem::Get: WorldContextObject is null."));
        checkf(false, TEXT("UGameStateSubsystem::Get: WorldContextObject is null."))
        return nullptr;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("UGameStateSubsystem::Get: Failed to get World from WorldContextObject."));
        checkf(false, TEXT("UGameStateSubsystem::Get: Failed to get World from WorldContextObject."))
        return nullptr;
    }

    UGameInstance* GameInstance = World->GetGameInstance();
    if (!GameInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("UGameStateSubsystem::Get: Failed to get GameInstance from World."));
        checkf(false, TEXT("UGameStateSubsystem::Get: WorldContextObject is null."));
        return nullptr;
    }

    UGameStateSubsystem* Subsystem = GameInstance->GetSubsystem<UGameStateSubsystem>();
    if (!Subsystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("UGameStateSubsystem::Get: Failed to get UGameStateSubsystem from GameInstance."));
        checkf(false, TEXT("UGameStateSubsystem::Get: WorldContextObject is null."))
    }
	
    return Subsystem;
}
