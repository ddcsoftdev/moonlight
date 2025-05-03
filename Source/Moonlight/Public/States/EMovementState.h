// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMovementState.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Walking     UMETA(DisplayName = "Walking"),
    Dashing     UMETA(DisplayName = "Dashing"),
    Stunned     UMETA(DisplayName = "Stunned"),
    Rooted      UMETA(DisplayName = "Rooted"),
    Pushed      UMETA(DisplayName = "Pushed"),
};
