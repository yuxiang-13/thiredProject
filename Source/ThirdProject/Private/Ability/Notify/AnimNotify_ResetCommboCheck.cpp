// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Notify/AnimNotify_ResetCommboCheck.h"

#include "Character/Core/Fight1Component.h"
#include "ThirdProject/ThirdProjectCharacter.h"

UAnimNotify_ResetCommboCheck::UAnimNotify_ResetCommboCheck()
{
}

FString UAnimNotify_ResetCommboCheck::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
	
}

void UAnimNotify_ResetCommboCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// 通过 骨骼体 获取UObject 强转 Character
	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		// 初始化 连击 Index
		Character->GetFightComponent()->GetComboCheck()->Reset();
	}

}
