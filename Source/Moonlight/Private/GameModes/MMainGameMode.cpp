// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/MMainGameMode.h"
#include "Controllers/MPlayerController.h"
#include "Characters/MPlayerCharacter.h"

#include "UObject/ConstructorHelpers.h"

AMMainGameMode::AMMainGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMPlayerCharacter::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Characters/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Controllers/Blueprints/BP_PlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}