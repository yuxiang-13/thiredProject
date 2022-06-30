// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Core/UI_Base.h"
#include "UI_EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API UUI_EnemyHealthBar : public UUI_Base
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;
public:
	void SetHealthBarPercent(float Num);
};
