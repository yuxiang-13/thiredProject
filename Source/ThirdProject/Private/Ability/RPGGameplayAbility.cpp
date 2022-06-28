// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/RPGGameplayAbility.h"

URPGGameplayAbility::URPGGameplayAbility()
{
	
	
}

void URPGGameplayAbility::OnCompleted()
{
	k2_OnCompleted();
}

void URPGGameplayAbility::OnBlendOut()
{
	k2_OnBlendOut();
}

void URPGGameplayAbility::OnInterrupted()
{
	k2_OnInterrupted();
}

void URPGGameplayAbility::OnCancelled()
{
	k2_OnCancelled();
}

// 接收伤害
void URPGGameplayAbility::OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData Payload)
{
	// 最后 GA 调用 Attribute
}

void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void URPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}

UAbilityTask_PlayMontageAndWait* URPGGameplayAbility::CreatePlayMontageAndWaitProxy(FName TaskInstanceName,
	UAnimMontage* InMontageToPlay, float Rate, FName StartSection, bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale, float StartTimeSeconds)
{
	
}

UAbilityTask_PlayMontageAndWait* URPGGameplayAbility::PlayMontage(FName StartSection)
{
	return CreatePlayMontageAndWaitProxy(NAME_None, MontageToPlay, 1.0f, StartSection);
}
