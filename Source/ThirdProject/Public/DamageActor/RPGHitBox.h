// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "RPGHitBox.generated.h"

//Biueprintabie可以被蓝图类继承，该说明符会传递给派生头
//B1ueprintType可用于蓝图的变量类型
//DisplayName="Blueprint Node Name”蓝图中的节点名

UCLASS(BlueprintType, Blueprintable)
class THIRDPROJECT_API ARPGHitBox : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "HitCollision")
	class USceneComponent* HitCollisionRootComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "HitCollision")
	class UBoxComponent* HitDamage;

public:
	UPROPERTY()
		TArray<FGameplayTag> BuffsTags;

	// 存着 重叠目标
	UPROPERTY()
		TArray<class APGCharacterBase*> AttackedTarget;
	
public:	
	// 有参 可以修改父类 中变量
	ARPGHitBox(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	virtual void HandleDamage (UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	// 返回碰撞盒子 函数
	virtual UPrimitiveComponent* GetHitDamage();

	// 设置 碰撞盒子 位置函数
	void SetHitDamageRelativePosition(const FVector& inNewPoation);

	// 设置盒子 大小
	void SetBoxExtent(const FVector & InNewBoxExtent);

	// 设置GAS标签（激活哪种能力）告诉系统.们要激发哪个能力
	void SetBuffs(const TArray<FGameplayTag>& InBuffs);

	// 是否造成效果
	bool IsExist(ACharacter* InNewTaget) const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
