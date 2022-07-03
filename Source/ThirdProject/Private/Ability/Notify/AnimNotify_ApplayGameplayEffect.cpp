// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Notify/AnimNotify_ApplayGameplayEffect.h"

#include "DamageActor/RPGHirBox_ApplayGameEffect.h"


UAnimNotify_ApplayGameplayEffect::UAnimNotify_ApplayGameplayEffect()
	:Super()
{
	HitObjectClass = ARPGHirBox_ApplayGameEffect::StaticClass();
	BoxExtent = FVector(32.f);
	LifeTime = 4.0f;
	//去骨骼里面添加这个插槽
	InSocketName = TEXT("OpenFire");

}

FString UAnimNotify_ApplayGameplayEffect::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_ApplayGameplayEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	Super::Notify(MeshComp, Animation);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
	//	if ((InCharacter->GetLocalRole() == ENetRole::ROLE_Authority))
		{
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		//只在服务器上生成actor
	//	if (InCharacter->GetWorld()->IsServer())
		{
			//有待探讨  四元锁 欧拉角的问题
			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);

			FString VForward = ComponentLocation.ToString();

			if (ARPGHirBox_ApplayGameEffect* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<ARPGHirBox_ApplayGameEffect>(
				HitObjectClass,
				Transform,
				NULL,
				Cast<APawn>(InCharacter),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn))

			{
				//延迟生成但是还没有生成 
				//


				
				//构造体的预初始化 
				HitCollision->PreInitCollision(InCharacter);
				//设置激活的GE类
				HitCollision->SetGameplayEffect(EffectClass);

				HitCollision->SetBoxExtent(BoxExtent);

				//设置相对位置
				FVector RelativeLocation = HitCollision->GetHitDamage()->GetRelativeLocation();
				HitCollision->SetHitDamageRelativePosition(RelativeLocation + RelativeOffsetLocation);
				HitCollision->SetActorRotation(ComponentRotation + RotationOffset);
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
}