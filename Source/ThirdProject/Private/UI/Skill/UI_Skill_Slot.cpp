// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Skill/UI_Skill_Slot.h"

#include "Abilities/GameplayAbility.h"
#include "Character/Core/PGCharacterBase.h"
#include "Components/Image.h"

int32 UUI_Skill_Slot::P1ayerSkillNumber = 0;
	
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
}

void UUI_Skill_Slot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	
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

void UUI_Skill_Slot::OnClickWidget()
{
	if (APGCharacterBase* InCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<APGCharacterBase>())
	{
		// 玩家激活技能
		InCharacter->ActiveSkillByString(Tags.ToString());
	}
}
