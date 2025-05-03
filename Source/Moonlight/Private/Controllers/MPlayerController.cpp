// Copyright Epic Games, Inc. All Rights Reserved.

#include "Controllers/MPlayerController.h"
#include "Characters/MPlayerCharacter.h"
#include "Subsystems/GameStateSubsystem.h"
#include "Components/InputStateComponent.h"

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"


AMPlayerController::AMPlayerController()
{
	//Components
	InputStateComponent = CreateDefaultSubobject<UInputStateComponent>(TEXT("InputStateComponent"));
	//bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Default;
}

void AMPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

AMPlayerCharacter* const AMPlayerController::GetPlayerCharacter()
{
	if (!GetCharacter())
	{
		return nullptr;
	}
	if (AMPlayerCharacter* PlayerCharacter = Cast<AMPlayerCharacter>(GetCharacter()))
	{
		return PlayerCharacter;
	}
	return nullptr;
}

void AMPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		checkf(InputStateComponent, TEXT("InputStateComponent Not Found"));
		for (FEnhancedActionKeyMapping Mapping : DefaultMappingContext->GetMappings())
		{
			InputStateComponent->AddInput(Mapping.Action);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(FaceDownAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnFaceDownPressed);
		EnhancedInputComponent->BindAction(FaceLeftAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnFaceLeftPressed);
		EnhancedInputComponent->BindAction(FaceRightAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnFaceRightPressed);
		EnhancedInputComponent->BindAction(FaceUpAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnFaceUpPressed);
		EnhancedInputComponent->BindAction(FaceDownAction, ETriggerEvent::Completed, this, &AMPlayerController::OnFaceDownRelease);
		EnhancedInputComponent->BindAction(FaceLeftAction, ETriggerEvent::Completed, this, &AMPlayerController::OnFaceLeftRelease);
		EnhancedInputComponent->BindAction(FaceRightAction, ETriggerEvent::Completed, this, &AMPlayerController::OnFaceRightRelease);
		EnhancedInputComponent->BindAction(FaceUpAction, ETriggerEvent::Completed, this, &AMPlayerController::OnFaceUpRelease);

		EnhancedInputComponent->BindAction(BumperRightAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnBumperRightPressed);
		EnhancedInputComponent->BindAction(BumperLeftAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnBumperLeftPressed);
		EnhancedInputComponent->BindAction(TriggerRightAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnTriggerRightPressed);
		EnhancedInputComponent->BindAction(TriggerLeftAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnTriggerLeftPressed);
		EnhancedInputComponent->BindAction(BumperRightAction, ETriggerEvent::Completed, this, &AMPlayerController::OnBumperRightRelease);
		EnhancedInputComponent->BindAction(BumperLeftAction, ETriggerEvent::Completed, this, &AMPlayerController::OnBumperLeftRelease);
		EnhancedInputComponent->BindAction(TriggerRightAction, ETriggerEvent::Completed, this, &AMPlayerController::OnTriggerRightRelease);
		EnhancedInputComponent->BindAction(TriggerLeftAction, ETriggerEvent::Completed, this, &AMPlayerController::OnTriggerLeftRelease);

		EnhancedInputComponent->BindAction(RightStickAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnRightStickInputPressed);
		EnhancedInputComponent->BindAction(LeftStickAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnLeftStickInputPressed);
		EnhancedInputComponent->BindAction(RightStickClickAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnRightStickClickPressed);
		EnhancedInputComponent->BindAction(LeftStickClickAction, ETriggerEvent::Triggered, this, &AMPlayerController::OnLeftStickClickPressed);
		EnhancedInputComponent->BindAction(RightStickAction, ETriggerEvent::Completed, this, &AMPlayerController::OnRightStickInputReleased);
		EnhancedInputComponent->BindAction(LeftStickAction, ETriggerEvent::Completed, this, &AMPlayerController::OnLeftStickInputReleased);
		EnhancedInputComponent->BindAction(RightStickClickAction, ETriggerEvent::Completed, this, &AMPlayerController::OnRightStickClickRelease);
		EnhancedInputComponent->BindAction(LeftStickClickAction, ETriggerEvent::Completed, this, &AMPlayerController::OnLeftStickClickRelease);

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
		case EGameState::StoryMode:
			if (AMPlayerCharacter* PlayerCharacter = GetPlayerCharacter())
			{
				if (InputStateComponent->GetInputState(FaceDownAction) == EInputState::Unpressed)
				{
					PlayerCharacter->PlayerDash();
				}
			}
			break;
		case EGameState::Menu:
			break;

		case EGameState::Initializing:
		case EGameState::Saving:
		case EGameState::Loading:
		case EGameState::ShuttingDown:
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(FaceDownAction, GetWorld());
}

void AMPlayerController::OnFaceLeftPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(FaceLeftAction, GetWorld());
}

void AMPlayerController::OnFaceRightPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(FaceRightAction, GetWorld());
}

void AMPlayerController::OnFaceUpPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(FaceUpAction, GetWorld());
}

void AMPlayerController::OnFaceDownRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(FaceDownAction, GetWorld());
}

void AMPlayerController::OnFaceLeftRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(FaceLeftAction, GetWorld());
}

void AMPlayerController::OnFaceRightRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(FaceRightAction, GetWorld());
}

void AMPlayerController::OnFaceUpRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(FaceUpAction, GetWorld());
}

void AMPlayerController::OnBumperRightPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(BumperRightAction, GetWorld());
}

void AMPlayerController::OnBumperLeftPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(BumperLeftAction, GetWorld());
}

void AMPlayerController::OnTriggerRightPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(TriggerRightAction, GetWorld());
}

void AMPlayerController::OnTriggerLeftPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(TriggerLeftAction, GetWorld());
}

void AMPlayerController::OnBumperRightRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(BumperRightAction, GetWorld());
}

void AMPlayerController::OnBumperLeftRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(BumperLeftAction, GetWorld());
}

void AMPlayerController::OnTriggerRightRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(TriggerRightAction, GetWorld());
}

void AMPlayerController::OnTriggerLeftRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(TriggerLeftAction, GetWorld());
}

void AMPlayerController::OnRightStickInputPressed(const FInputActionValue& Value)
{
	if (UGameStateSubsystem* Subsystem = UGameStateSubsystem::Get(this))
	{
		switch (Subsystem->GetGameState())
		{
		case EGameState::ActionMode:
		case EGameState::StoryMode:
			break;
		case EGameState::Menu:
			break;

		case EGameState::Initializing:
		case EGameState::Saving:
		case EGameState::Loading:
		case EGameState::ShuttingDown:
			return;
		default:
			return;
		}
	}
	InputStateComponent->SetInputStatePressed(RightStickAction, GetWorld());
}

void AMPlayerController::OnLeftStickInputPressed(const FInputActionValue& Value)
{
	if (UGameStateSubsystem* Subsystem = UGameStateSubsystem::Get(this))
	{
		switch (Subsystem->GetGameState())
		{
		case EGameState::ActionMode:
		case EGameState::StoryMode:
			if (AMPlayerCharacter* PlayerCharacter = GetPlayerCharacter())
			{
				FVector2D Direction = Value.Get<FVector2D>();
				PlayerCharacter->MoveCharacter(Direction);
			}
			break;
		case EGameState::Menu:
			break;

		case EGameState::Initializing:
		case EGameState::Saving:
		case EGameState::Loading:
		case EGameState::ShuttingDown:
			return;
		default:
			return;
		}
	}
	InputStateComponent->SetInputStatePressed(LeftStickAction, GetWorld());
}

void AMPlayerController::OnRightStickClickPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(RightStickClickAction, GetWorld());
}

void AMPlayerController::OnRightStickInputReleased(const FInputActionValue& Value)
{
	if (UGameStateSubsystem* Subsystem = UGameStateSubsystem::Get(this))
	{
		switch (Subsystem->GetGameState())
		{
		case EGameState::ActionMode:
		case EGameState::StoryMode:

		case EGameState::Menu:
			break;

		case EGameState::Initializing:
		case EGameState::Saving:
		case EGameState::Loading:
		case EGameState::ShuttingDown:
			return;
		default:
			return;
		}
	}
	InputStateComponent->SetInputStateReleased(RightStickAction, GetWorld());
}

void AMPlayerController::OnLeftStickInputReleased(const FInputActionValue& Value)
{
	if (UGameStateSubsystem* Subsystem = UGameStateSubsystem::Get(this))
	{
		switch (Subsystem->GetGameState())
		{
		case EGameState::ActionMode:
		case EGameState::StoryMode:

			break;
		case EGameState::Menu:
			break;

		case EGameState::Initializing:
		case EGameState::Saving:
		case EGameState::Loading:
		case EGameState::ShuttingDown:
			return;
		default:
			return;
		}
	}
	InputStateComponent->SetInputStateReleased(LeftStickAction, GetWorld());
}


void AMPlayerController::OnLeftStickClickPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(LeftStickClickAction, GetWorld());
}

void AMPlayerController::OnRightStickClickRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(RightStickClickAction, GetWorld());
}

void AMPlayerController::OnLeftStickClickRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(LeftStickClickAction, GetWorld());
}

void AMPlayerController::OnDPadUpPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(FaceUpArrowAction, GetWorld());
}

void AMPlayerController::OnDPadLeftPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(FaceLeftArrowAction, GetWorld());
}

void AMPlayerController::OnDPadRightPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(FaceRightArrowAction, GetWorld());
}

void AMPlayerController::OnDPadDownPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(FaceDownArrowAction, GetWorld());
}

void AMPlayerController::OnDPadUpRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(FaceUpArrowAction, GetWorld());
}

void AMPlayerController::OnDPadLeftRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(FaceLeftArrowAction, GetWorld());
}

void AMPlayerController::OnDPadRightRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(FaceRightArrowAction, GetWorld());
}

void AMPlayerController::OnDPadDownRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(FaceDownArrowAction, GetWorld());
}

void AMPlayerController::OnStartPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(StartAction, GetWorld());
}

void AMPlayerController::OnSelectPressed()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStatePressed(SelectAction, GetWorld());
}

void AMPlayerController::OnStartRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(StartAction, GetWorld());
}

void AMPlayerController::OnSelectRelease()
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
			return;
		default:
			return;
		}
	}

	InputStateComponent->SetInputStateReleased(SelectAction, GetWorld());
}

#pragma endregion
