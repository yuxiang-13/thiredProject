// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameplayAbility.generated.h"

/**
* GameplayAbility（GA） 技能本身
技能GameplayAbility是角色可以使用的能力，比如跳跃、攻击、火球术、次元斩等。创建不同的技能是GAS的一个主要工作。在GA中可以触发不同的技能任务（AbilityTask），它们承担了诸如播放动画、角色移动等持续一段时间的功能。
 */
UCLASS()
class THIRDPROJECT_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
};
