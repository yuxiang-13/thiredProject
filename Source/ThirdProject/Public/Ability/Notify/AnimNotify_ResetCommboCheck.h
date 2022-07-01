// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ResetCommboCheck.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API UAnimNotify_ResetCommboCheck : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_ResetCommboCheck();

	// 编辑器看到的名字
	virtual FString GetNotifyName_Implementation() const override;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
