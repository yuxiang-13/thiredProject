// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AddForce.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName="AddForce"))
class THIRDPROJECT_API UAnimNotifyState_AddForce: public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_AddForce();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	// 力 大小 和方向
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Force")
		FVector DirectionForce;
	// 力大小
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Force")
		float Forceize;
private:
	//总共消耗的时间,就是这个通知的时长
	float TotalDurationConsuming;

	//力大小
	float ForcesizeConsuming;

	// 玩家当前 方向
	FVector GetCurrentCharacterDirection(class APGCharacterBase* InCharacter);

};
