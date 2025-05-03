// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UInputStateComponent;

UCLASS()
class AMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMPlayerController();

#pragma region INPUT
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FaceDownAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FaceLeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FaceRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FrontUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BumperRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BumperLeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TriggerRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TriggerLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RightStickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftStickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RightStickClickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftStickClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FaceUpArrowAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FaceLeftArrowAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FaceRightArrowAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FaceDownArrowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StartAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SelectAction;

protected:
	void OnFaceDownPressed();
	void OnFaceLeftPressed();
	void OnFaceRightPressed();
	void OnFaceUpPressed();

	void OnFaceDownRelease();
	void OnFaceLeftRelease();
	void OnFaceRightRelease();
	void OnFaceUpRelease();

	void OnBumperRightPressed();
	void OnBumperLeftPressed();
	void OnTriggerRightPressed();
	void OnTriggerLeftPressed();

	void OnBumperRightRelease();
	void OnBumperLeftRelease();
	void OnTriggerRightRelease();
	void OnTriggerLeftRelease();

	void OnRightStickInput(const FInputActionValue& Value);
	void OnLeftStickInput(const FInputActionValue& Value);
	void OnRightStickPressed();
	void OnLeftStickPressed();

	void OnRightStickRelease();
	void OnLeftStickRelease();

	void OnDPadUpPressed();
	void OnDPadLeftPressed();
	void OnDPadRightPressed();
	void OnDPadDownPressed();

	void OnDPadUpRelease();
	void OnDPadLeftRelease();
	void OnDPadRightRelease();
	void OnDPadDownRelease();

	void OnStartPressed();
	void OnSelectPressed();

	void OnStartRelease();
	void OnSelectRelease();
#pragma endregion INPUT

#pragma region COMPONENTS
	UInputStateComponent* InputStateComponent;

#pragma endregion COMPONENTS
protected:


	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

private:

};


