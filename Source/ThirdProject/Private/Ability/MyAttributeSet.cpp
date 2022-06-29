// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/MyAttributeSet.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UMyAttributeSet::UMyAttributeSet(): Health(100.f)
{
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// 属性改变之后 UI 相关处理

	UKismetSystemLibrary::PrintString(this,TEXT(" UMyAttributeSet:  PostGameplayEffectExecute "));
}

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	// 调用GAMEPLAYATTRIBUTE_REPNOTIFY 宏才能使用预测系统
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Health, OldValue);

}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UMyAttributeSet, Health);
}
