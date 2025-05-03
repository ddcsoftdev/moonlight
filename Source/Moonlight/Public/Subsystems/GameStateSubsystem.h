#pragma once

#include "States/EGameState.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameStateSubsystem.generated.h"

UCLASS()
class MOONLIGHT_API UGameStateSubsystem : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameStateSubsystem();

	virtual void Init() override;
	virtual void Shutdown() override;
	//Called after Init
	virtual void OnStart() override;

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