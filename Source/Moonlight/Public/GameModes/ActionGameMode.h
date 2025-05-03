// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActionGameMode.generated.h"

UCLASS(minimalapi)
class AActionGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AActionGameMode();

	virtual void BeginPlay() override;
};



