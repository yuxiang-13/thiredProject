// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSkillDataTable: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FSkillDataTable();

	// 指向角色 的 ID
	UPROPERTY(EditDefaultsOnly, Category="CharacterSkill")
		int32 CharacterID;

	// 图标
	UPROPERTY(EditDefaultsOnly, Category="CharacterSkill")
		class UTexture2D* Icon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Characterskill")
	TSubclassOf<class UGameplayAbility> GameplayAbility;

};
