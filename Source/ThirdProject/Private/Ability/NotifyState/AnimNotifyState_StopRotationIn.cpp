// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NotifyState/AnimNotifyState_StopRotationIn.h"

#include "ThirdProject/ThirdProjectCharacter.h"

UAnimNotifyState_StopRotationIn::UAnimNotifyState_StopRotationIn()
{
}

void UAnimNotifyState_StopRotationIn::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	
	// 通过 骨骼体 获取UObject 强转 Character
	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		Character->bUseControllerRotationYaw = false;
	}

	
}

void UAnimNotifyState_StopRotationIn::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_StopRotationIn::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		Character->bUseControllerRotationYaw = true;
	}
}
