// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor/RPGHirBox_ApplayGameEffect.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "Ability/RPGAbilitySystemComponent.h"
#include "Character/Core/PGCharacterBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


ARPGHirBox_ApplayGameEffect::ARPGHirBox_ApplayGameEffect(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HitCollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	HitDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(HitCollisionRootComponent);

	// 存活周期
	InitialLifeSpan = 1.0f;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	// 最大速度
	ProjectileMovement->MaxSpeed = 2000.f;
	// 默认速度
	ProjectileMovement->InitialSpeed = 1600.f;
	//关闭重力，不关重力就是抛物线
	ProjectileMovement->ProjectileGravityScale = 0.f;

	// 控制移动
	ProjectileMovement->SetUpdatedComponent(RootComponent) ;


	HitCollisionType = EHitCollisionType::HITCOLLISIONTYPE_SHORT_RANGE_ATTACK;
}

void ARPGHirBox_ApplayGameEffect::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//首先排除白己,在通知攻击函数里面传入,是谁生成了它
	// 此处设置 自定义碰撞 更好
	if (GetInstigator() != OtherActor)
	{
		if (APGCharacterBase* InPawn = Cast<APGCharacterBase>(OtherActor))
		{
			if (InPawn)
			{
				//传给GAs的事件数据
				FGameplayEventData EventData;
				EventData.Instigator = GetInstigator();
				EventData.Target = InPawn;
				
				//已经对该对象产生伤害
				if (IsExist(InPawn))
				{
					return;
				}

				// 添加 唯一
				AttackedTarget.AddUnique(InPawn);
				//拿到一个cAs
				if(URPGAbilitySystemComponent* InAbilitySystemComponent = InPawn->GetAbilitySystemComponent())
				{
					// 获取上下文
					FGameplayEffectContextHandle EffectContext = InAbilitySystemComponent->MakeEffectContext();
					// 添加 原目标
					EffectContext.AddSourceObject(InPawn);

					// 创建 GE 的 Handle 实例
					FGameplayEffectSpecHandle EffectSpecHandle = InAbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);
					
					if (EffectSpecHandle.IsValid())
					{
						// 执行GE
						InAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), InAbilitySystemComponent);
					}

				}
				InPawn->PlayHit();
			}
		}
	}
}

UPrimitiveComponent* ARPGHirBox_ApplayGameEffect::GetHitDamage()
{
	return HitDamage;
}

void ARPGHirBox_ApplayGameEffect::SetHitDamageRelativePosition(const FVector& inNewPoation)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetRelativeLocation(inNewPoation);
	}
}

void ARPGHirBox_ApplayGameEffect::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);
}

// Called when the game starts or when spawned
void ARPGHirBox_ApplayGameEffect::BeginPlay()
{
	Super::BeginPlay();

	HitDamage->OnComponentBeginOverlap.AddDynamic(this, &ARPGHirBox_ApplayGameEffect::HandleDamage);
}

// Called every frame
void ARPGHirBox_ApplayGameEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ARPGHirBox_ApplayGameEffect::IsExist(ACharacter* InNewTaget) const
{
	for (auto& Tmp : AttackedTarget)
	{
		if(IsValid(Tmp))
		{
			if (Tmp == InNewTaget)
			{
				return true;
			}
		}
	}

	return false;
}



void ARPGHirBox_ApplayGameEffect::PreInitCollision(AActor* InMyInstigator)
{
	if (!InMyInstigator)
	{
		return;
	}

	
	// 获取 发起者 向前的向量
	FVector ShootDirection = InMyInstigator->GetActorForwardVector();
	
	switch (HitCollisionType)
	{
	case EHitCollisionType::HITCOLLISIONTYPE_SHORT_RANGE_ATTACK: //近程攻击
		{
			// 最大速度
			ProjectileMovement->MaxSpeed = 0.f;
			// 默认速度
			ProjectileMovement->InitialSpeed = 0.f;
			//关闭重力，不关重力就是抛物线
			ProjectileMovement->ProjectileGravityScale = 0.f;
			break;
		}
	case EHitCollisionType::HITCOLLISIONTYPE_DIRECT_LINE:     //无障碍直线玫击工
		{
			RootComponent->SetWorldRotation(FRotator::ZeroRotator);
			ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;

			
			FString VForward = ProjectileMovement->Velocity.ToString();
			// FString::Printf 格式话字符串
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT(",%s"), *VForward));

			
			break;
		}
	case EHitCollisionType::HITCOLLISIONTYPE_LINE:
		{

			break;
		}
	case EHitCollisionType::HITCOLLISIONTYPE_TRACK_LINE:
		{

			break;
		}
	case EHitCollisionType::HITCOLLISIONTYPE_RANGE_LINE:
		{

			break;
		}
	case EHitCollisionType::HITCOLLISIONTYPE_RANGE:
		{

			break;
		}
	case EHitCollisionType::HITCOLLISIONTYPE_CHAIN:
		{

			break;
		}
	}
    
}