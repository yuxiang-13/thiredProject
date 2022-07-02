// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Attack.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API UAttack : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAttack();


	TArray<FGameplayTag> BuffTags;
};
