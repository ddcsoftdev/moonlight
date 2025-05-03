// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGameState.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
    Initializing    UMETA(DisplayName = "Initializing"),
    Menu            UMETA(DisplayName = "Menu"),
    ActionMode      UMETA(DisplayName = "ActionMode"),
    StoryMode       UMETA(DisplayName = "StoryMode"),
    Saving          UMETA(DisplayName = "Saving"),
    Loading         UMETA(DisplayName = "Loading"),
    ShuttingDown    UMETA(DisplayName = "ShuttingDown"),
};
