// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Slot_Base.h"
#include "DataTable/SkillDataTable.h"
#include "UI/Core/UI_Base.h"
#include "UI_Skill_Slot.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API UUI_Skill_Slot : public UUI_Slot_Base
{
	GENERATED_BODY()
public:
	// 技能ICon
	UPROPERTY(meta=(BindWidget))
	class UImage* SlotImage;
	// 冷却数字
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* SlotCDValue;
	// 冷却图片
	UPROPERTY(meta=(BindWidget))
	class UImage* SlotCD;
	
	//CD动态材质UPROPERTYo
	UPROPERTY()
	class UMaterialInstanceDynamic* CDMaterialDynamic;
public:
	//绘制材质CL
	void DrawSlotCDMat(float InSlotCD);

	// 对应的的标整。由它的上级传入
	FName Tags;
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//由面板调用。更新GA的信息到s1ot上
	void Update(const FSkillDataTable InSkillDataTable);

	UPROPERTY()
		float CoolDown;
	UPROPERTY()
		float MaxCoolDown;


public:
	// 儅激活时触发，有蓝图配置 映射输入
	virtual void OnClickWidget();
protected:
	// 按鍵映射
	int32 KayNumber;

	// 用来拼接 按键映射
	FString KayString;

	// 共有靜態變量用來排序
	static int32 P1ayerSkillNumber;

};
