// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Task/RPGAbilityTask_PMAW.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

URPGAbilityTask_PMAW::URPGAbilityTask_PMAW()
{
}

void URPGAbilityTask_PMAW::Activate()
{
	
	//Ability 就是 调用这个的
	if(Ability == nullptr){
		return;
	}

	if (AbilitySystemComponent)
	{
		// 获取 施法者 信息
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		// 获取 施法者 动画实例
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		
		if(AnimInstance) {
			//绑定 承伤 代理
			EventHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(
				EventTags,
				FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &URPGAbilityTask_PMAW::OnDamageGameplayEvent)
			);

		}

	}

	Super::Activate();
}

void URPGAbilityTask_PMAW::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	if (AbilitySystemComponent)
	{
		//的把自己的tag移除了
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}
}

URPGAbilityTask_PMAW* URPGAbilityTask_PMAW::CreatePMAWDamageEventProxy(UGameplayAbility* OwningAbility,
	FName TaskInstanceName, UAnimMontage* MontageToPlay, FGameplayTagContainer InEventTags, float Rate,
	FName StartSection, bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale, float StartTimeSeconnds)
{
	// 应用能力
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);


	
	// 创建 这个能力
	URPGAbilityTask_PMAW* MyObj = NewAbilityTask<URPGAbilityTask_PMAW> (OwningAbility, TaskInstanceName);
	MyObj->MontageToPlay = MontageToPlay;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	MyObj->StartTimeSeconds = StartTimeSeconnds;
	MyObj->EventTags = InEventTags;
	return MyObj;
}

void URPGAbilityTask_PMAW::OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData* Payload)
{
	//TASK 执行完了，我需要回调GA告诉GA 你的表现执行完了你可以继续往下走了（表现 蒙太奇执行结束了）
	// 
	if (ShouldBroadcastAbilityTaskDelegates()) {
		FGameplayEventData EventData = *Payload; // 标签
		EventData.EventTag = InGameplayTag; // 项目信息

		// 广播 回到GA了
		DamageEventReceived.Broadcast(InGameplayTag, EventData);
	};
}
