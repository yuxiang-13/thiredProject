// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NotifyState/AnimNotifyState_CheckCombo.h"

#include "Character/Core/Fight1Component.h"
#include "ThirdProject/ThirdProjectCharacter.h"

UAnimNotifyState_CheckCombo::UAnimNotifyState_CheckCombo()
{
}

void UAnimNotifyState_CheckCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() && MeshComp->GetOuter()->GetWorld()->IsServer())
	{

		// 通过 骨骼体 获取UObject 强转 Character
		if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
			// 鼠标 短按 置为 false ， 消耗连击变量(就是开始3连攻击，每次的开始都置为 false)
			Character->GetFightComponent()->GetComboCheck()->bShortPress = false;
			// 这个连击已经播放，引导到下一个连击
			Character->GetFightComponent()->GetComboCheck()->UpdateComboIndex();
			UE_LOG(LogTemp, Log,TEXT("NotifyBegin  设置连击为  %i"), Character->GetFightComponent()->GetComboCheck()->ComboIndex);
		}
	}
}

void UAnimNotifyState_CheckCombo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_CheckCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	
	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() && MeshComp->GetOuter()->GetWorld()->IsServer())
	{

		// 通过 骨骼体 获取UObject 强转 Character
		if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
			if (Character->GetFightComponent()->GetComboCheck()->bLongPress || Character->GetFightComponent()->GetComboCheck()->bShortPress)
			{
				// 触发技能 （触发GA）
				Character->ActiveSkillByString("Character.Skill.ComboAttack");
				UE_LOG(LogTemp, Log,TEXT("NotifyEnd  设置连击为  %i"), Character->GetFightComponent()->GetComboCheck()->ComboIndex);
			}
		}
	}

}




