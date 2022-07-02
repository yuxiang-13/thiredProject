// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/NotifyState/AnimNotifyState_AddForce.h"

#include "Character/Core/PGCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ThirdProject/ThirdProjectCharacter.h"

UAnimNotifyState_AddForce::UAnimNotifyState_AddForce()
	:DirectionForce (1.0f,0.f,0.f),
	Forceize(180000.f),
	TotalDurationConsuming(0.f),
	ForcesizeConsuming(0.f)
{
	
}

void UAnimNotifyState_AddForce::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	//总共消耗的时间,就是这个通知的时长
	//把时间赋值过来
	TotalDurationConsuming = TotalDuration;

	
	//每次判定消耗后的残值力，当开始时这个力时满值，结束时是0
	//把编辑器里面的力赋值过来
	ForcesizeConsuming = Forceize;


	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		FVector Newrirection = GetCurrentCharacterDirection(Character);
		Character->GetCharacterMovement()->AddImpulse(Forceize * Newrirection, true);
	}

}

//总共消耗的时间,就是这个通知的时长
void UAnimNotifyState_AddForce::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	// // 通知的时间，大于0，才可行
	// if (TotalDurationConsuming > 0)
	// {
	// 	
	// 	// 通过 骨骼体 获取UObject 强转 Character
	// 	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
	// 		FVector NewFirection = GetCurrentCharacterDirection(Character);
	//
	// 		
	// 		Character->GetCharacterMovement()->AddForce(ForcesizeConsuming * NewFirection);
	// 		if ( ForcesizeConsuming>0.f)
	// 		{
	// 			//每秒帧教
	// 			float PresecondFrame = 1.0f/ FrameDeltaTime;//这段时间的总消耗帧数
	// 			float TotalFrame = TotalDurationConsuming * PresecondFrame;//每帧应该减去多少力
	// 			float FrameAttenuationFrameDeltaTime = Forceize / TotalFrame;
	// 			//对的力进行衰减
	// 			ForcesizeConsuming -= FrameAttenuationFrameDeltaTime;
	// 		}
	//
	// 		
	// 	}
	// }

	
}

//每次判定消耗后的残值力，当开始时这个力时满值，结束时是0
void UAnimNotifyState_AddForce::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	
	if (AThirdProjectCharacter* Character = Cast<AThirdProjectCharacter>(MeshComp->GetOuter())){
		Character->GetCharacterMovement()->StopMovementImmediately();
	}
}

// 玩家当前 方向
FVector UAnimNotifyState_AddForce::GetCurrentCharacterDirection(APGCharacterBase* InCharacter)
{
	FVector V = FVector::ZeroVector;
	if (InCharacter)
	{
		if (DirectionForce.X != 0)
		{
			V.X += DirectionForce.X * DirectionForce.X;
		}
		if (DirectionForce.Y != 0)
		{
			V.Y += DirectionForce.Y * DirectionForce.Y;
		}
		if (DirectionForce.Z != 0)
		{
			V.Z += DirectionForce.Z * DirectionForce.Z;
		}
	}
	
	
	return V;
}