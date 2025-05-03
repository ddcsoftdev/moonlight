// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EInputState.generated.h"

UENUM(BlueprintType)
enum class EInputState : uint8
{
    Pressed     UMETA(DisplayName = "Pressed"),
    Hold        UMETA(DisplayName = "Hold"),
    Released    UMETA(DisplayName = "Released"),
    Unpressed    UMETA(DisplayName = "Unpressed"),
};
