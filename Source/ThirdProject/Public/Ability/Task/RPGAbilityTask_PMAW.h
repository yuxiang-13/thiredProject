// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "RPGAbilityTask_PMAW.generated.h"

// 多播
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMontageWaitSimpleForDamageEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

/**
 * 
 */

// GA激活以后 来 task工作。task工作完后，回到GA, 通过这个代理告诉GA 执行结束
UCLASS()
class THIRDPROJECT_API URPGAbilityTask_PMAW : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()
public:
	URPGAbilityTask_PMAW();

	// 伤害事件代理
	UPROPERTY(BlueprintAssignable)
		FMontageWaitSimpleForDamageEventDelegate DamageEventReceived;

	// 激活
	virtual void Activate() override;
	// 销毁
	virtual void OnDestroy(bool bInOwnerFinished) override;

	// GA调用这个，让task工作
	static URPGAbilityTask_PMAW* CreatePMAWDamageEventProxy(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* MontageToPlay,
		FGameplayTagContainer InEventTags,
		float Rate = 1.0f,
		FName StartSection = NAME_None,
		bool bStopWhenAbilityEnds = true,
		float AnimRootMotionTranslationScale = 1.0f,
		float StartTimeSeconnds = 0.f
	);

private:
	// 自身 handle
	FDelegateHandle EventHandle;
private:
	// 由gas通知我task，我task通过代理，告诉ga我结束完了可以执行后续了
	void OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData* Payload);

private:
	// 标签
	UPROPERTY()
	FGameplayTagContainer EventTags;

};
