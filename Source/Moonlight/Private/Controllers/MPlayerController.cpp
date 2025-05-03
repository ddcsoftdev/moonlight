// Copyright Epic Games, Inc. All Rights Reserved.

#include "Controllers/MPlayerController.h"
#include "Characters/MPlayerCharacter.h"
#include "Subsystems/GameStateSubsystem.h"

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputActionValue.h"


AMPlayerController::AMPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AMPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AMPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(FaceDownAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnFaceDownPressed);
		EnhancedInputComponent->BindAction(FaceLeftAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnFaceLeftPressed);
		EnhancedInputComponent->BindAction(FaceRightAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnFaceRightPressed);
		EnhancedInputComponent->BindAction(FrontUpAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnFaceUpPressed);
		EnhancedInputComponent->BindAction(FaceDownAction, ETriggerEvent::Completed, this, &AMPlayerController::OnFaceDownRelease);
		EnhancedInputComponent->BindAction(FaceLeftAction, ETriggerEvent::Completed, this, &AMPlayerController::OnFaceLeftRelease);
		EnhancedInputComponent->BindAction(FaceRightAction, ETriggerEvent::Completed, this, &AMPlayerController::OnFaceRightRelease);
		EnhancedInputComponent->BindAction(FrontUpAction, ETriggerEvent::Completed, this, &AMPlayerController::OnFaceUpRelease);

		EnhancedInputComponent->BindAction(BumperRightAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnBumperRightPressed);
		EnhancedInputComponent->BindAction(BumperLeftAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnBumperLeftPressed);
		EnhancedInputComponent->BindAction(TriggerRightAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnTriggerRightPressed);
		EnhancedInputComponent->BindAction(TriggerLeftAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnTriggerLeftPressed);
		EnhancedInputComponent->BindAction(BumperRightAction, ETriggerEvent::Completed, this, &AMPlayerController::OnBumperRightRelease);
		EnhancedInputComponent->BindAction(BumperLeftAction, ETriggerEvent::Completed, this, &AMPlayerController::OnBumperLeftRelease);
		EnhancedInputComponent->BindAction(TriggerRightAction, ETriggerEvent::Completed, this, &AMPlayerController::OnTriggerRightRelease);
		EnhancedInputComponent->BindAction(TriggerLeftAction, ETriggerEvent::Completed, this, &AMPlayerController::OnTriggerLeftRelease);

		EnhancedInputComponent->BindAction(RightStickAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnRightStickInput);
		EnhancedInputComponent->BindAction(LeftStickAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnLeftStickInput);
		EnhancedInputComponent->BindAction(RightStickClickAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnRightStickPressed);
		EnhancedInputComponent->BindAction(LeftStickClickAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnLeftStickPressed);
		EnhancedInputComponent->BindAction(RightStickClickAction, ETriggerEvent::Completed, this, &AMPlayerController::OnRightStickRelease);
		EnhancedInputComponent->BindAction(LeftStickClickAction, ETriggerEvent::Completed, this, &AMPlayerController::OnLeftStickRelease);

		EnhancedInputComponent->BindAction(FaceUpArrowAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnDPadUpPressed);
		EnhancedInputComponent->BindAction(FaceLeftArrowAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnDPadLeftPressed);
		EnhancedInputComponent->BindAction(FaceRightArrowAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnDPadRightPressed);
		EnhancedInputComponent->BindAction(FaceDownArrowAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnDPadDownPressed);
		EnhancedInputComponent->BindAction(FaceUpArrowAction, ETriggerEvent::Completed, this, &AMPlayerController::OnDPadUpRelease);
		EnhancedInputComponent->BindAction(FaceLeftArrowAction, ETriggerEvent::Completed, this, &AMPlayerController::OnDPadLeftRelease);
		EnhancedInputComponent->BindAction(FaceRightArrowAction, ETriggerEvent::Completed, this, &AMPlayerController::OnDPadRightRelease);
		EnhancedInputComponent->BindAction(FaceDownArrowAction, ETriggerEvent::Completed, this, &AMPlayerController::OnDPadDownRelease);
		
		EnhancedInputComponent->BindAction(StartAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnStartPressed);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnSelectPressed);
		EnhancedInputComponent->BindAction(StartAction, ETriggerEvent::Completed, this, &AMPlayerController::OnStartRelease);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &AMPlayerController::OnSelectRelease);
	}
	else
	{
	}
}


#pragma region INPUT
void AMPlayerController::OnFaceDownPressed()
{
	if (UGameStateSubsystem* Subsystem = UGameStateSubsystem::Get(this))
	{
		switch (Subsystem->GetGameState())
		{
		case EGameState::ActionMode:
			break;

		case EGameState::StoryMode:
			break;
		case EGameState::Menu:
			break;

		case EGameState::Initializing:
		case EGameState::Saving:
		case EGameState::Loading:
		case EGameState::ShuttingDown:
			break;
		default:

		}
	}
}

void AMPlayerController::OnFaceLeftPressed()
{
}

void AMPlayerController::OnFaceRightPressed()
{
}

void AMPlayerController::OnFaceUpPressed()
{
}

void AMPlayerController::OnFaceDownRelease()
{
}

void AMPlayerController::OnFaceLeftRelease()
{
}

void AMPlayerController::OnFaceRightRelease()
{
}

void AMPlayerController::OnFaceUpRelease()
{
}

void AMPlayerController::OnBumperRightPressed()
{
}

void AMPlayerController::OnBumperLeftPressed()
{
}

void AMPlayerController::OnTriggerRightPressed()
{
}

void AMPlayerController::OnTriggerLeftPressed()
{
}

void AMPlayerController::OnBumperRightRelease()
{
}

void AMPlayerController::OnBumperLeftRelease()
{
}

void AMPlayerController::OnTriggerRightRelease()
{
}

void AMPlayerController::OnTriggerLeftRelease()
{
}

void AMPlayerController::OnRightStickInput(const FInputActionValue& Value)
{
}

void AMPlayerController::OnLeftStickInput(const FInputActionValue& Value)
{
}

void AMPlayerController::OnRightStickPressed()
{
}

void AMPlayerController::OnLeftStickPressed()
{
}

void AMPlayerController::OnRightStickRelease()
{
}

void AMPlayerController::OnLeftStickRelease()
{
}

void AMPlayerController::OnDPadUpPressed()
{
}

void AMPlayerController::OnDPadLeftPressed()
{
}

void AMPlayerController::OnDPadRightPressed()
{
}

void AMPlayerController::OnDPadDownPressed()
{
}

void AMPlayerController::OnDPadUpRelease()
{
}

void AMPlayerController::OnDPadLeftRelease()
{
}

void AMPlayerController::OnDPadRightRelease()
{
}

void AMPlayerController::OnDPadDownRelease()
{
}

void AMPlayerController::OnStartPressed()
{
}

void AMPlayerController::OnSelectPressed()
{
}

void AMPlayerController::OnStartRelease()
{
}

void AMPlayerController::OnSelectRelease()
{
}

#pragma endregion
