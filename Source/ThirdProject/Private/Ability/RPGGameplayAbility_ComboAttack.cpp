// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/RPGGameplayAbility_ComboAttack.h"

#include "Character/Core/Fight1Component.h"
#include "ThirdProject/ThirdProjectCharacter.h"

URPGGameplayAbility_ComboAttack::URPGGameplayAbility_ComboAttack()
{
}

void URPGGameplayAbility_ComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 开始执行 能力,失败 直接返回
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}


	AThirdProjectCharacter * Character = Cast<AThirdProjectCharacter>(ActorInfo->OwnerActor);
	if (Character)
	{
		// 成功,播放 蒙太奇
		if (PlayMontage(*FString::FromInt(Character->GetFightComponent()->GetComboCheck()->ComboIndex)))
		{
			UE_LOG(LogTemp, Log,TEXT("ComboAttack 为  %i"), Character->GetFightComponent()->GetComboCheck()->ComboIndex);
		}
	}
}
