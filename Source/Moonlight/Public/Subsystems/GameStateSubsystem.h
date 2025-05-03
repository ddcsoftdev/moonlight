#pragma once

#include "States/EGameState.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameStateSubsystem.generated.h"

UCLASS()
class MOONLIGHT_API UGameStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UGameStateSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Override Deinitialize to clean up (if needed)
	virtual void Deinitialize() override;

	// Example function to access this instance from anywhere
	UFUNCTION(BlueprintCallable, Category = "Game")
	static UGameStateSubsystem* Get(const UObject* WorldContextObject);

private:
	EGameState GameState;

#pragma region GET/SET
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE enum EGameState GetGameState() const { return GameState; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetGameState(EGameState State) { GameState = State; }
#pragma endregion

};