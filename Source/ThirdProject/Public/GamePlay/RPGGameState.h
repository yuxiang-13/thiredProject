// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DataTable/SkillDataTable.h"
#include "GameFramework/GameStateBase.h"
#include "RPGGameState.generated.h"


class UGameplayAbility;
/**
 * 
 */
UCLASS()
class THIRDPROJECT_API ARPGGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ARPGGameState();

	TArray<UGameplayAbility*> GetCharacterSkills(int32 InCharacterID);
	// 获取所有技能
	TArray<FSkillDataTable*> GetCharacterSkillTables();
	
protected:
	UPROPERTY()
	class UDataTable* SkillDataPtr;
	
	TArray<FSkillDataTable*> SkillDataTables;
};
