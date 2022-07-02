// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_StopRotationIn.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName="StopRotationIn"))
class THIRDPROJECT_API UAnimNotifyState_StopRotationIn : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UAnimNotifyState_StopRotationIn();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
