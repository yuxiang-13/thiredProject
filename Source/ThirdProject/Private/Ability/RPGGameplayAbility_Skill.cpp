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


	// // 如果从"激活"中调用`CommitAbility`函数，它将应用执行技能的消耗 作者：_jiejie_cj https://www.bilibili.com/read/cv8433798/ 出处：bilibili
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
