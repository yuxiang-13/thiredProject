// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RPGAttributeMacros.h"
#include "MyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMyAttributeSet();
	
	// 血
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	PROPERTY_FUNCTION_REGISTRATION(UMyAttributeSet, Health)

	
	// 最大血
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
	PROPERTY_FUNCTION_REGISTRATION(UMyAttributeSet, MaxHealth)

	// 蓝
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Mana)
		FGameplayAttributeData Mana;
	PROPERTY_FUNCTION_REGISTRATION(UMyAttributeSet, Mana)
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
