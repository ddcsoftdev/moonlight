// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "States/EInputState.h"

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnhancedInputComponent.h"
#include "InputStateComponent.generated.h"

USTRUCT()
struct FInputState
{
	GENERATED_BODY()
public:
	FInputState() 
	{
		MappingKey = nullptr;
		State = EInputState::Unpressed;
		TimerHandle = FTimerHandle();
		ElapsedTime = 0.0f;
	}

	FInputState(const UInputAction* Key)
	{
		MappingKey = Key;
		State = EInputState::Unpressed;
		TimerHandle = FTimerHandle();
		ElapsedTime = 0.0f;
	}
private:
	const UInputAction* MappingKey;
	EInputState State;
	FTimerHandle TimerHandle;
	float ElapsedTime;
public:
	FORCEINLINE void SetMappingKey(const UInputAction* Key) { if (MappingKey == nullptr) MappingKey = Key; }
	FORCEINLINE const UInputAction* GetMappingKey() { return MappingKey; }
	FORCEINLINE EInputState GetState() { return State; }
	/*Ticks each 0.1 seconds*/
	FORCEINLINE float GetElaspedTime() { return ElapsedTime; }

	void SetState(EInputState NewState, UWorld* WorldRef = nullptr)
	{
		if (WorldRef)
		{
			WorldRef->GetTimerManager().ClearTimer(TimerHandle);
			switch (NewState)
			{
			case EInputState::Pressed:
				WorldRef->GetTimerManager().SetTimer(TimerHandle,[this](){ ElapsedTime += 0.1f; },0.1f, true);
				break;
			case EInputState::Released:
				ElapsedTime = 0.0f;
				float TimeToChange = MappingKey->Triggers[0] ? MappingKey->Triggers[0].Get()->ActuationThreshold : 0.25f;
				WorldRef->GetTimerManager().SetTimer(TimerHandle, [this]() { SetState(EInputState::Unpressed); }, TimeToChange, false);
				break;
			}
			this->State = NewState;
		}
		else
		{
			switch (NewState)
			{
			case EInputState::Hold:
			case EInputState::Unpressed:
				this->State = NewState;
				return;

			}
			checkf(false, TEXT("WorldRef not valid"));
		}

	}

};

UCLASS()
class MOONLIGHT_API UInputStateComponent : public UObject
{
	GENERATED_BODY()

public:
	UInputStateComponent();
	UInputStateComponent(TArray<const UInputAction*> Mappings);

protected:
	TMap<const UInputAction*, FInputState> Inputs;

#pragma region GET/SET
public:
	FORCEINLINE TMap<const UInputAction*, FInputState> GetInputs() const { return Inputs; }
	FORCEINLINE FInputState* GetInput(const UInputAction* Key) { check(Inputs.Contains(Key)); return Inputs.Find(Key); }
	FORCEINLINE void AddInput(const UInputAction* Key) { FInputState Input = FInputState(Key); Inputs.Add(Key, Input); }
	FORCEINLINE void RemoveInput(const UInputAction* Key, FInputState Input) { Inputs.Remove(Key); }

	FORCEINLINE EInputState GetInputState(const UInputAction* Key) { return GetInput(Key)->GetState(); }
	FORCEINLINE float GetInputTimeElapsed(const UInputAction* Key) { return GetInput(Key)->GetElaspedTime(); }
	FORCEINLINE void SetInputStatePressed(const UInputAction* Key) { GetInput(Key)->SetState(EInputState::Pressed); }
	FORCEINLINE void SetInputStateReleased(const UInputAction* Key) { GetInput(Key)->SetState(EInputState::Released); }

#pragma endregion
};
