// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

#include "Components/HealthComponent.h"
#include "Components/MovementDataComponent.h"

AMCharacter::AMCharacter()
{
	//componentes
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	MovementDataComponent = CreateDefaultSubobject<UMovementDataComponent>(TEXT("MovementDataComponent"));

}

void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


