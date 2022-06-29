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
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,true,false);
}

void URPGGameplayAbility::OnBlendOut()
{
	k2_OnBlendOut();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,true,false);
}

void URPGGameplayAbility::OnInterrupted()
{
	k2_OnInterrupted();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,true,false);
}

void URPGGameplayAbility::OnCancelled()
{
	k2_OnCancelled();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,true,false);
}
// 激活某个能力
void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

// 接收伤害
void URPGGameplayAbility::OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData Payload)
{
	// 最后 GA 调用 Attribute
	UE_LOG(LogTemp, Log, TEXT("- -- ->>>>   "));
	
	//先创建—个目标数组
	FGameplayAbilityTargetData_ActorArray* NewTargetData_Actorlrray = new FGameplayAbilityTargetData_ActorArray();
	//把我们的命中传递过来的数据中的目标添进数组
	NewTargetData_Actorlrray->TargetActorArray.Add(const_cast<AActor*>(Payload.Instigator));
	
	//创建目标数据的handle
	FGameplayAbilityTargetDataHandle TargetHandleData;
	//把我们的数据添加到处理目标数据的handle里面
	TargetHandleData.Add(NewTargetData_Actorlrray);
	
	
	//1 创建GE handle
	// 从所有激活的GE 遍历（find 找对应GA激活的GE,这里全部激活）
	for (auto &Tmp: EffectMap)
	{
		//1 创建GE Handle
			//拿到我们的 GAs系统组件(通过GA的激活信息)
			//创建GE的实例, GE本体, GE的等级, GE的上下文信息
		FGameplayEffectSpecHandle NewGEHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
			Tmp.Value,
			1,
			MakeEffectContext(CurrentSpecHandle, CurrentActorInfo)
		);
		
		//2 GEHandle创建成功
		if(NewGEHandle.IsValid())
		{
			// 找到 GA 的实例 （通过 GA 的 Handle 获取 GA 的实例）
			FGameplayAbilitySpec* AbilitySpec = GetAbilitySystemComponentFromActorInfo()->FindAbilitySpecFromHandle(CurrentSpecHandle);
			
			
			//3 把GA捕获的信息，应用到GE上
			ApplyAbilityTagsToGameplayEffectSpec(*NewGEHandle.Data.Get(), AbilitySpec);
		
			if(AbilitySpec)
			{
				NewGEHandle.Data->SetByCallerTagMagnitudes = AbilitySpec->SetByCallerTagMagnitudes;
			}
		}
	
	
		// 蓝图函数    这块触发了  属性的 UMyAttributeSet::PostGameplayEffectExecute
		TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandle = K2_ApplyGameplayEffectSpecToTarget(NewGEHandle, TargetHandleData);
	}
}
