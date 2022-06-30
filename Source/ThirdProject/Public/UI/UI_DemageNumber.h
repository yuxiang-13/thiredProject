// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "UI/Core/UI_Base.h"
#include "UI_DemageNumber.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API UUI_DemageNumber : public UUI_Base
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	 class UTextBlock* DamageNum;
public:
	virtual void NativeConstruct() override;

	void UpdateDemage(const FText & InText);
};
