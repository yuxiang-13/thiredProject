// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Attack.generated.h"


class ARPGHitBox;
/**
 * 
 */
UCLASS(meta = (DisplayName = "Attack"))
class THIRDPROJECT_API UAttack : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAttack();

	// 获取 通知名字
	virtual FString GetNotifyName_Implementation() const override;

	// 通知
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	//触发那个tag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	TArray<FGameplayTag> BuffTags;

	//生成哪一个盒体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	TSubclassOf<ARPGHitBox> HitObjectClass;


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
