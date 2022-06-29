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

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	PROPERTY_FUNCTION_REGISTRATION(UMyAttributeSet, Health)

	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
