// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "RPGHirBox_ApplayGameEffect.generated.h"

//这是个定义磁童类型的枚举UENUMN(BiueprintType)
UENUM(BlueprintType)
enum class EHitCollisionType: uint8
{
	HITCOLLISIONTYPE_SHORT_RANGE_ATTACK        UMETA(DisplayName = "Short range attack"),//近程攻击
	HITCOLLISIONTYPE_DIRECT_LINE            UMETA(DisplayName = "Direct Line"),    //无障碍直线玫击工
	HITCOLLISIONTYPE_LINE                    UMETA(DisplayName = "Line" ), //非跟路类型,类似手枪子单:
	HITCOLLISIONTYPE_TRACK_LINE                UMETA(DisplayName = "Track Line"), //跟踪类型
	HITCOLLISIONTYPE_RANGE_LINE                UMETA(DisplayName = "Range Line"), //范围伤吉，丢手雷:
	HITCOLLISIONTYPE_RANGE                    UMETA(DisplayName = "Range"), //范围伤害，类似白爆:
	HITCOLLISIONTYPE_CHAIN                    UMETA(DisplayName = "Chain") //链条类型,持续伤害类型:
};


 
UCLASS(BlueprintType, Blueprintable)
class THIRDPROJECT_API ARPGHirBox_ApplayGameEffect : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "HitCollision")
	class USceneComponent* HitCollisionRootComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "HitCollision")
	class UBoxComponent* HitDamage;


	// 投掷组件
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "HitCollision")
	class UProjectileMovementComponent* ProjectileMovement;
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "HitCollision")
	EHitCollisionType HitCollisionType;
     
	
public:	
	// Sets default values for this actor's properties
	ARPGHirBox_ApplayGameEffect(const FObjectInitializer& ObjectInitializer);
	
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
	void SetGameplayEffect(TSubclassOf<UGameplayEffect>& InGE) { EffectClass = InGE; };

	// 是否造成效果
	bool IsExist(ACharacter* InNewTaget) const;

	
	//这个是用来在初始化之前设置磁碰撞类型的函数
	virtual void PreInitCollision(AActor* InMyInstigator);


     
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
	TSubclassOf<UGameplayEffect> EffectClass;

	// 存着 重叠目标
	UPROPERTY()
	TArray<class APGCharacterBase*> AttackedTarget;
};
