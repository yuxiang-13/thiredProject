// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/RPGGameplayAbility.h"

#include "Ability/Task/RPGAbilityTask_PMAW.h"
#include "ThirdProject/ThirdProjectCharacter.h"

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
	UE_LOG(LogTemp, Log, TEXT("- -- ->>>>   "));

	
}

// 激活某个能力
void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// 开始执行 能力，失败 直接返回
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
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

// task告诉执行蒙太奇
UAbilityTask_PlayMontageAndWait* URPGGameplayAbility::PlayMontage(FName StartSection)
{
	return CreatePlayMontageAndWaitProxy(NAME_None, MontageToPlay, 1.0f, StartSection);
}

// 创建 UAbilityTask
UAbilityTask_PlayMontageAndWait* URPGGameplayAbility::CreatePlayMontageAndWaitProxy(FName TaskInstanceName,
	UAnimMontage* InMontageToPlay, float Rate, FName StartSection, bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale, float StartTimeSeconds)
{
	// 创建 task
	URPGAbilityTask_PMAW* InWait = URPGAbilityTask_PMAW::CreatePMAWDamageEventProxy(
		this,
		TaskInstanceName,
		InMontageToPlay,
		AbilityTags,
		Rate,
		StartSection,
		bStopWhenAbilityEnds,
		AnimRootMotionTranslationScale,
		StartTimeSeconds
	);

	// 任务成功, 把GA函数绑定到task
	if (InWait)
	{
		InWait->OnCompleted.AddDynamic(this, &URPGGameplayAbility::OnCompleted);
		InWait->OnCompleted.AddDynamic(this, &URPGGameplayAbility::OnBlendOut);
		InWait->OnCompleted.AddDynamic(this, &URPGGameplayAbility::OnInterrupted);
		InWait->OnCompleted.AddDynamic(this, &URPGGameplayAbility::OnCancelled);
		//  绑定 task结束的委托
		InWait->DamageEventReceived.AddDynamic(this, &URPGGameplayAbility::OnDamageGameplayEvent);

		// task创建后了 参数也好了,开始激活task
		InWait->Activate();
		return  InWait;
	}
	return  NULL;
}



void URPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
									 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
									 bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}