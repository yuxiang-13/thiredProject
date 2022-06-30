// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/MyAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Character/Core/PGCharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UMyAttributeSet::UMyAttributeSet(): Health(50.f), Mana(50.f), MaxHealth(100.f)
{
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// 属性改变之后 UI 相关处理

	UKismetSystemLibrary::PrintString(this,TEXT(" UMyAttributeSet:  PostGameplayEffectExecute "));

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	// 标签
	const FGameplayTagContainer& soureourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}
	

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	APGCharacterBase* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<APGCharacterBase>(TargetActor);
	}
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		if (TargetCharacter)
		{
			TargetCharacter->HandleHealthChanged(GetHealth() / GetMaxHealth());
		}
	}
}

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	// 调用GAMEPLAYATTRIBUTE_REPNOTIFY 宏才能使用预测系统
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Health, OldValue);

}

void UMyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Mana, OldValue);
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Mana, OldValue);
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UMyAttributeSet, Health);
	DOREPLIFETIME(UMyAttributeSet, Mana);
	DOREPLIFETIME(UMyAttributeSet, MaxHealth);
}
