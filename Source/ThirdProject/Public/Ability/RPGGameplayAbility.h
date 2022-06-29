// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "RPGGameplayAbility.generated.h"

class UAbilityTask_PlayMontageAndWait;
/**
* GameplayAbility（GA） 技能本身
技能GameplayAbility是角色可以使用的能力，比如跳跃、攻击、火球术、次元斩等。创建不同的技能是GAS的一个主要工作。在GA中可以触发不同的技能任务（AbilityTask），它们承担了诸如播放动画、角色移动等持续一段时间的功能。
 */


UCLASS()
class THIRDPROJECT_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	// 攻击动画
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GSA")
	class UAnimMontage* MontageToPlay;

	// 带有的buff
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GamePlayEffect")
		TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> EffectMap;
	
public:
	URPGGameplayAbility();

	// 绑定到蒙太奇的 4 函数
	
	UFUNCTION()
	virtual void OnCompleted();
	
	UFUNCTION()
	virtual void OnBlendOut();
	
	UFUNCTION()
	virtual void OnInterrupted();
	
	UFUNCTION()
	virtual void OnCancelled();

	//技能 （产生效果）
	UFUNCTION()
	virtual void OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData Payload);

	// 激活
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	// 结束
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle, // GA 技能 handle
		const FGameplayAbilityActorInfo* ActorInfo, // 
		const FGameplayAbilityActivationInfo ActivationInfo, // 激活者信息
		bool bReplicateEndAbility, bool bWasCancelled) override;  // 可复制 可取消

	// 蓝图内实现吧	
	UFUNCTION(BlueprintImplementableEvent, Category=Ability, DisplayName = "OnCompleted", meta = (ScriptName = "OnCompleted"))
		void k2_OnCompleted();
	
	UFUNCTION(BlueprintImplementableEvent, Category=Ability, DisplayName = "OnBlendOut", meta = (ScriptName = "OnBlendOut"))
		void k2_OnBlendOut();
	
	UFUNCTION(BlueprintImplementableEvent, Category=Ability, DisplayName = "OnInterrupted", meta = (ScriptName = "OnInterrupted"))
		void k2_OnInterrupted();
	
	UFUNCTION(BlueprintImplementableEvent, Category=Ability, DisplayName = "Cancelled", meta = (ScriptName = "Cancelled"))
		void k2_OnCancelled();

	// 创建 UAbilityTask
	UFUNCTION(BlueprintCallable, Category="MMOARPGGameplayAbility", meta = (DisplayName = "PalyMontageAndWait"))
		UAbilityTask_PlayMontageAndWait* CreatePlayMontageAndWaitProxy(
			FName TaskInstanceName,
			UAnimMontage* InMontageToPlay,
			float Rate = 1.f,
			FName StartSection = NAME_None,
			bool bStopWhenAbilityEnds = true,
			float AnimRootMotionTranslationScale = 1.0f,
			float StartTimeSeconds = 1.0f
		);

	// 播放
	UFUNCTION(BlueprintCallable, Category= "MMOARPGGameplayAbility")
		UAbilityTask_PlayMontageAndWait* PlayMontage(FName StartSection = NAME_None);
};
