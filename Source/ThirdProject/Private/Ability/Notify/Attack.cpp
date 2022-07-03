// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Notify/Attack.h"

#include "DamageActor/RPGHitBox.h"

UAttack::UAttack()
	:Super()
{
	HitObjectClass = ARPGHitBox::StaticClass();
	BoxExtent = FVector(32.f);
	LifeTime = 4.0f;
	//去骨骼里面添加这个插槽
	InSocketName = TEXT("OpenFire");

}

FString UAttack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	Super::Notify(MeshComp, Animation);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{

		// 位置
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		// 旋转
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		//只在服务器上生成actor
		if (InCharacter->GetWorld()->IsServer())
		{
			//有待探讨  四元锁 欧拉角的问题
			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);

			// SpawnActorDeferred 延迟生成
			if (ARPGHitBox* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<ARPGHitBox>(
				HitObjectClass,
				Transform,
				NULL,
				Cast<APawn>(InCharacter),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn))

			{
				//延迟生成但是还没有生成 
				
				//设置激活的目标
				HitCollision->BuffsTags = BuffTags;
				HitCollision->SetBoxExtent(BoxExtent);
				
				//设置相对位置
				FVector RelativeLocation = HitCollision->GetHitDamage()->GetRelativeLocation();
				HitCollision->SetHitDamageRelativePosition(RelativeLocation + RelativeOffsetLocation);
				//	HitCollision->SetActorRotation(ComponentRotation + RotationOffset);
				//设置生命周期
				HitCollision->SetLifeSpan(LifeTime);
				
				//结束延迟生成
				HitCollision->FinishSpawning(Transform);

				//必须保证对象生成后再附加，否则附加会失败
				if (bBind)
				{

					HitCollision->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, InSocketName);
				}
			}
		}
	}
}