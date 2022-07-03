// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Skill/UI_Skill_Slot.h"

#include "Abilities/GameplayAbility.h"
#include "Character/Core/PGCharacterBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

int32 UUI_Skill_Slot::P1ayerSkillNumber = 0;

void UUI_Skill_Slot::DrawSlotCDMat(float InSlotCD)
{
	if (CDMaterialDynamic)
	{
		if (InSlotCD > 0.0f && InSlotCD < 1.0f)
		{
			CDMaterialDynamic->SetScalarParameterValue(FName("Param"), true);
			SlotCD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		} else
		{
			
			CDMaterialDynamic->SetScalarParameterValue(FName("Param"), false);
			SlotCD->SetVisibility(ESlateVisibility::Hidden);
		}

		CDMaterialDynamic->SetScalarParameterValue(FName("Param"), InSlotCD);

	}
}

void UUI_Skill_Slot::NativeConstruct()
{
	Super::NativeConstruct();

	if (P1ayerSkillNumber == 6)
	{
		P1ayerSkillNumber = 0;
	}

	// 做按鍵輸入，藍圖中配置
	KayNumber = ++P1ayerSkillNumber;
	KayString = FString::FromInt(KayNumber);
	FString InPlayerSkil1Name = FString::Printf(TEXT("PlayerSkill_%i"), P1ayerSkillNumber);

	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction(*InPlayerSkil1Name, IE_Pressed, this, &UUI_Skill_Slot::OnClickWidget);

	//关联图片的动态材质
	CDMaterialDynamic = SlotCD->GetDynamicMaterial();

	
}

void UUI_Skill_Slot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CoolDown > 0.f)
	{
		SlotCDValue->SetVisibility(ESlateVisibility::HitTestInvisible);
		CoolDown -= InDeltaTime;
		DrawSlotCDMat(1 - CoolDown / MaxCoolDown);
		SlotCDValue->SetText(FText::FromString( FString::Printf(TEXT("%.1f"), CoolDown)));
	} else
	{
		SlotCDValue->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UUI_Skill_Slot::Update(const FSkillDataTable InSkillDataTable)
{
	SlotImage->SetBrushFromTexture(InSkillDataTable.Icon);

	if(UGameplayAbility* GA = Cast<UGameplayAbility>(InSkillDataTable.GameplayAbility->GetDefaultObject()))
	{
		FString GATag = GA->AbilityTags.ToStringSimple();
		Tags = FName(GATag);
	}
}

void UUI_Skill_Slot::StartUpdateCD(float InCDValue)
{
	CoolDown = InCDValue;
}

void UUI_Skill_Slot::SetMaxCD(float InCDValue)
{
	MaxCoolDown = InCDValue;
}

void UUI_Skill_Slot::OnClickWidget()
{
	if (APGCharacterBase* InCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<APGCharacterBase>())
	{
		// 玩家激活技能
		InCharacter->ActiveSkillByString(Tags.ToString());
	}
}
