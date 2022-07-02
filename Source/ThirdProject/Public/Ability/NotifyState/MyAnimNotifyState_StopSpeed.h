// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAnimNotifyState_StopSpeed.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName="StopSpeed"))
class THIRDPROJECT_API UMyAnimNotifyState_StopSpeed : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UMyAnimNotifyState_StopSpeed();


	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


public:
	float MaxWalkSpeed;
};
