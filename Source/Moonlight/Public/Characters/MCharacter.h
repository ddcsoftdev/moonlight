// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"

class UHealthComponent;
class UMovementDataComponent;

UCLASS()
class MOONLIGHT_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

#pragma region MOVEMENT
public:


#pragma endregion MOVEMENT

protected:
	virtual void MoveCharacter(FVector2D Direction = FVector2D::ZeroVector) PURE_VIRTUAL(AMCharacter::MoveCharacter, );

#pragma region COMPONENTS
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MoonlightComponents, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MoonlightComponents, meta = (AllowPrivateAccess = "true"))
	UMovementDataComponent* MovementDataComponent;
#pragma endregion


#pragma region GET/SET
public:
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	FORCEINLINE class UMovementDataComponent* GetMovementDataComponent() const { return MovementDataComponent; }
#pragma endregion

};
