// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/RPGGameplayAbility_Skill.h"

#include "ThirdProject/ThirdProjectCharacter.h"

URPGGameplayAbility_Skill::URPGGameplayAbility_Skill()
{
}

void URPGGameplayAbility_Skill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	// // 开始执行 能力,失败 直接返回
	// if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	// {
	// 	return;
	// }

	// 强制冷却
	if (!CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, true))
	{
		return;
	}
	
	AThirdProjectCharacter * Character = Cast<AThirdProjectCharacter>(ActorInfo->OwnerActor);
	if (Character)
	{
		// 成功,播放 蒙太奇
		if (PlayMontage(*FString::FromInt(0)))
		{
		}
	}

	
}
