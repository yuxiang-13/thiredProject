// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_Base.h"
#include "UI_Main.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API UUI_Main : public UUI_Base
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
		class UProgressBar* Health;
	UPROPERTY(meta=(BindWidget))
		class UProgressBar* Mana;
	UPROPERTY(meta=(BindWidget))
		class UProgressBar* stamina;
public:
	UUI_Main(const FObjectInitializer& ObjectInitializer);

	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UFUNCTION()
		void UpdateHealthProgress(float InPercent);
	UFUNCTION()
		void UpdateManaProgress(float InPercent);
	UFUNCTION()
		void UpdateStaminaProgress(float InPercent);
private:
	float TargetHealth;
};
