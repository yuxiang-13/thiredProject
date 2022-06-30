// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/RPGGameState.h"

#include "DataTable/SkillDataTable.h"
#include "Engine/DataTable.h"

ARPGGameState::ARPGGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTable(TEXT("/Game/ThirdPerson/DataTable/SkillDataTable"));
	if (SkillDataTable.Object)
	{
		SkillDataPtr = SkillDataTable.Object;

		GetCharacterSkillTables();
	}
}

// 通过角色 ID 获取 GA 技能能力
TArray<UGameplayAbility*> ARPGGameState::GetCharacterSkills(int32 InCharacterID)
{
	TArray<UGameplayAbility*> Skills;
	if (SkillDataTables.Num() > 0)
	{
		for (auto &Tmp:  SkillDataTables)
		{
			if (Tmp->CharacterID == InCharacterID)
			{
				UGameplayAbility* NewAbility = Cast<UGameplayAbility>(Tmp->GameplayAbility.GetDefaultObject());
				Skills.Add(NewAbility);
			}
		}
	}
	return Skills;
}

// 把 DataTable 内的数据，保存到变量内
TArray<FSkillDataTable*> ARPGGameState::GetCharacterSkillTables()
{
	if (SkillDataPtr)
	{
		SkillDataTables.Empty();
		// 把 蓝图中DataTable 数据读取出来
		SkillDataPtr->GetAllRows(TEXT("Load SkillData Miss"), SkillDataTables);
	}
	return SkillDataTables;
}
