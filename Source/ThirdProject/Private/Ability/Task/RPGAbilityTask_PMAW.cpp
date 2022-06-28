// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Task/RPGAbilityTask_PMAW.h"

#include "AbilitySystemGlobals.h"

URPGAbilityTask_PMAW::URPGAbilityTask_PMAW()
{
}

void URPGAbilityTask_PMAW::Activate()
{
	Super::Activate();
}

void URPGAbilityTask_PMAW::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

URPGAbilityTask_PMAW* URPGAbilityTask_PMAW::CreatePMAWDamageEventProxy(UGameplayAbility* OwningAbility,
	FName TaskInstanceName, UAnimMontage* MontageToPlay, FGameplayTagContainer InEventTags, float Rate,
	FName StartSection, bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale, float StartTimeSeconnds)
{
	// 应用能力
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);
	// 创建 能力
	URPGAbilityTask_PMAWDamageEvent* MyObj = NewAbilityTask<URPGAbilityTask_PMAWDamageEvent>(OwningAbility, TaskInstanceName);
	
	return NULL;
}

void URPGAbilityTask_PMAW::OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData* Payload)
{
}
