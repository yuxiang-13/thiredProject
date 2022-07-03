// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Skill_Slot.h"
#include "UI/Core/UI_Base.h"
#include "UI_SkillPanel.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API UUI_SkillPanel : public UUI_Base
{
	GENERATED_BODY()
public:
	// 水平框用来放6个子类的框框
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* SlotArray;

	//指定生成的蓝图Slot
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUI_Skill_Slot> SkillS1otClass;

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//初始化布局
	void LayoutSlot();

	
};
