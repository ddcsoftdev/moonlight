// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GameStateSubsystem.h"
#include "UObject/ConstructorHelpers.h"



UGameStateSubsystem::UGameStateSubsystem()
{
}

void UGameStateSubsystem::Init()
{
	Super::Init();

	SetGameState(EGameState::Initializing);
	UE_LOG(LogTemp, Log, TEXT("UGameStateSubsystem: Initializing..."));
}

void UGameStateSubsystem::Shutdown()
{
	UE_LOG(LogTemp, Log, TEXT("UGameStateSubsystem: Shutting down..."));
	SetGameState(EGameState::ShuttingDown);

	Super::Shutdown();
}

void UGameStateSubsystem::OnStart()
{
	Super::OnStart();

	UE_LOG(LogTemp, Log, TEXT("UGameStateSubsystem: Game Starting"));
}

UGameStateSubsystem* UGameStateSubsystem::Get(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		UWorld* World = WorldContextObject->GetWorld();
		if (World) 
		{
			return Cast<UGameStateSubsystem>(World->GetGameInstance());
		}
		else 
		{
			checkf(false, TEXT("Failed to get World from WorldContextObject"));
		}
	}
	else
	{
		checkf(false, TEXT("Failed to get WorldContextObject"));
	}
	return nullptr;
}
