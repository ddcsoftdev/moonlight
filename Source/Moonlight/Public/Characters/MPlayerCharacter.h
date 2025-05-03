// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MCharacter.h"
#include "MPlayerCharacter.generated.h"

class UDamageComponent;
class UEnergyComponent;
class USpellComponent;
class UTalentComponent;

UCLASS()
class MOONLIGHT_API AMPlayerCharacter : public AMCharacter
{
	GENERATED_BODY()

public:
	AMPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region COMPONENTS
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MoonlightComponents, meta = (AllowPrivateAccess = "true"))
	UDamageComponent* DamageComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MoonlightComponents, meta = (AllowPrivateAccess = "true"))
	UEnergyComponent* EnergyComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MoonlightComponents, meta = (AllowPrivateAccess = "true"))
	USpellComponent* SpellComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MoonlightComponents, meta = (AllowPrivateAccess = "true"))
	UTalentComponent* TalentComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
#pragma endregion


#pragma region GET/SET
public:
	FORCEINLINE class UDamageComponent* GetDamageComponent() const { return DamageComponent; }
	FORCEINLINE class UEnergyComponent* GetEnergyComponent() const { return EnergyComponent; }
	FORCEINLINE class USpellComponent* GetSpellComponent() const { return SpellComponent; }
	FORCEINLINE class UTalentComponent* GetTalentComponent() const { return TalentComponent; }

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
#pragma endregion

};
