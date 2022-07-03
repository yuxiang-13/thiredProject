// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Skill/UI_SkillPanel.h"

#include "Character/Core/PGCharacterBase.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "GamePlay/RPGGameState.h"

void UUI_SkillPanel::NativeConstruct()
{
	Super::NativeConstruct();
	LayoutSlot();

	// if (APGCharacterBase* InCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<APGCharacterBase>())

	if (APlayerController* InPlayerController = GetWorld()->GetFirstPlayerController<APlayerController>()) 
	{
		if (APGCharacterBase* InCharacter = InPlayerController->GetPawn<APGCharacterBase>())
		{
			InCharacter->UpdateSkillCooldownDelegate.BindUObject(this, &UUI_SkillPanel::UpdateSkillCD);
		}
	}
	
}

void UUI_SkillPanel::UpdateSkillCD(const FName& InTagNum, float InCDValue)
{
	auto FindTemp = [&](UUI_Skill_Slot* InSkillBlot)
	{
		if (InSkillBlot->Tags == InTagNum)
		{
			InSkillBlot->StartUpdateCD(InCDValue);
			InSkillBlot->SetMaxCD(InCDValue);
			return true;
		} else
		{
			return false;
		}
	};


	if (SlotArray)
	{
		for (int32 i = 0; i < SlotArray->GetChildrenCount(); i++)
		{
			// 执行更新 CD 函数
			if (FindTemp(Cast<UUI_Skill_Slot>(SlotArray->GetChildAt(i))))
			{
				break;
			}
		}
	}
	
}

void UUI_SkillPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_SkillPanel::LayoutSlot()
{
	if (SkillS1otClass)
	{
		// 获取角色
		if (APGCharacterBase* InCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<APGCharacterBase>())
		{
			// 
			if (ARPGGameState* InGameState = GetWorld()->GetGameState<ARPGGameState>())
			{
				int32 CharacterID = InCharacter->GetCharacterID();
				//拿到所有的技能信息
				TArray<FSkillDataTable*>SkillTables = InGameState->GetCharacterSkillTables(CharacterID);

				int32 j = 0;
				for(size_t i = 0; i < 6; i++)
				{
					if (UUI_Skill_Slot* SlotWidget = CreateWidget<UUI_Skill_Slot>(GetWorld(), SkillS1otClass))
					{
						//添加到我们的水平技能框里面
						if(UHorizontalBoxSlot* GridSlot = SlotArray->AddChildToHorizontalBox(SlotWidget))
						{
							//遍历技能数据进行更新
							if (SkillTables.Num() > 0)
							{
								for (; j < SkillTables.Num(); j++)
								{
									//拿到这个J位置的GA
									if (UGameplayAbility* GA = Cast<UGameplayAbility>(SkillTables[j]->GameplayAbility->GetDefaultObject()))
									{
										FString GATag = GA->AbilityTags.ToStringSimple();
										//如果是的话,就跳出去,寻找下一个GA
										if(GATag == "Character.State.Die" || GATag == "Character.State.Hit")
										{
											continue;
										}
									}

									//如果是主动技能，就更新slot
									SlotWidget->Update(*SkillTables[i]);
									j++;
									//这个插槽更新完毕了，不再循环，下个插槽继续更新，继续循环，从同一个位置
									//如果Skilltales循环完了，就不再简环

									break;
								}
							}
						}
					}
				}
			}
		}
	}
}