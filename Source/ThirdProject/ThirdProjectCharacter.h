// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability/RPGAbilitySystemComponent.h"
#include "Ability/RPGGameplayAbility.h"
#include "Character/Core/PGCharacterBase.h"
#include "GameFramework/Character.h"
#include "ThirdProjectCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FUpdateProqressstate, float)

UCLASS(config=Game)
class AThirdProjectCharacter : public APGCharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// //2 能力
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	// TSubclassOf<class UGameplayAbility> GameplayAbilityAbility;
	//
	// // 能力3
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	// TSubclassOf<class UGameplayAbility> InGameplayAbility2;

	// 绑定给 MainUI 的代理
	FUpdateProqressstate UpdateHealthProgress;
	FUpdateProqressstate UpdateManaProgress;
	FUpdateProqressstate UpdateStanProgress;
	


public:
	void HandleHealthChanged(float InHealthPercent) override;

	void UpdateHealth(float Num);
	void UpdateMana(float Num);
	void UpdateStan(float Num);
	
	AThirdProjectCharacter();

	void BeginPlay() override;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	void ComboAttackOnPressed();
	void ComboAttackOnReleased();
protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

