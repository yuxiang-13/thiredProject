// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NotifyState/MyAnimNotifyState_StopSpeed.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ThirdProject/ThirdProjectCharacter.h"

UMyAnimNotifyState_StopSpeed::UMyAnimNotifyState_StopSpeed()
	:MaxWalkSpeed(0.f)
{
}

void UMyAnimNotifyState_StopSpeed::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	// 通过 骨骼体 获取UObject 强转 Character
	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		MaxWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeed = 0.f;
	}
}

void UMyAnimNotifyState_StopSpeed::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UMyAnimNotifyState_StopSpeed::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	// 通过 骨骼体 获取UObject 强转 Character
	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		Character->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}
