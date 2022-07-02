// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NotifyState/AnimNotifyState_IgnoreInput.h"

#include "ThirdProject/ThirdProjectCharacter.h"

UAnimNotifyState_IgnoreInput::UAnimNotifyState_IgnoreInput()
{
}

void UAnimNotifyState_IgnoreInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	// 通过 骨骼体 获取UObject 强转 Character
	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		Character->DisableInput(Character->GetWorld()->GetFirstPlayerController());
	}
}

void UAnimNotifyState_IgnoreInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_IgnoreInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	// 通过 骨骼体 获取UObject 强转 Character
	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		Character->EnableInput(Character->GetWorld()->GetFirstPlayerController());
	}
}
