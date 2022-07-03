// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ApplayGameplayEffect.generated.h"

class ARPGHitBox_ApplyGameEffect;
/**
 * 
 */
UCLASS(meta = (DisplayName = "ApplyGameplayEffect"))
class THIRDPROJECT_API UAnimNotify_ApplayGameplayEffect : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_ApplayGameplayEffect();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	//应用哪一个GE的实例
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	TSubclassOf<UGameplayEffect> EffectClass;

	
	//生成哪一个盒体 匹配生成的盒体才能产生响应的效果
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	TSubclassOf<ARPGHitBox_ApplyGameEffect> HitObjectClass;


	//碰撞体的相对位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FVector RelativeOffsetLocation;

	//碰撞体的相对旋转
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FRotator RotationOffset;


	//存在的生命周期
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	float LifeTime;

	//生成在骨骼体的哪一个部分上
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	FName InSocketName;

	//将Box绑定在角色身上开火点上  静态的还是移动的
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	bool bBind;

	//BOx的大小
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Box")
	FVector BoxExtent;
};
