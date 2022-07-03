// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/RPGGameplayAbility.h"
#include "RPGGameplayAbility_Skill.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API URPGGameplayAbility_Skill : public URPGGameplayAbility
{
	GENERATED_BODY()
public:
	URPGGameplayAbility_Skill();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void CallUpdateCoolDown();
};
