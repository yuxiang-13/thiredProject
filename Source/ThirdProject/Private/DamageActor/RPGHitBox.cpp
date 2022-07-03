// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor/RPGHitBox.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/Core/PGCharacterBase.h"
#include "Components/BoxComponent.h"

ARPGHitBox::ARPGHitBox(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HitCollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	HitDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(HitCollisionRootComponent);

	// 存活周期
	InitialLifeSpan = 4.0f;
	// 
}

void ARPGHitBox::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APGCharacterBase* InCharacter = Cast<APGCharacterBase>(OtherActor))
	{
		// 添加 唯一
		AttackedTarget.AddUnique(InCharacter);
	}
	//首先排除白己,在通知攻击函数里面传入,是谁生成了它
	// 此处设置 自定义碰撞 更好
	if (GetInstigator() != OtherActor)
	{
		if (APGCharacterBase* InPawn = Cast<APGCharacterBase>(GetInstigator()))
		{
			APGCharacterBase* Enemy = Cast<APGCharacterBase>(OtherActor);
			if (Enemy)
			{
				//传给GAs的事件数据
				FGameplayEventData EventData;
				EventData.Instigator = GetInstigator();
				EventData.Target = Enemy;
				
				//已经对该对象产生伤害
				if (IsExist(InPawn))
				{
					return;
				}
				if(!BuffsTags.IsEmpty()) { //BuffsTags
					for (auto& Tmp :BuffsTags)
					{
						//数据上的处理受伤
						UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), Tmp, EventData);
					}
				}
				Enemy->PlayHit();
			}
		}
	}
}

UPrimitiveComponent* ARPGHitBox::GetHitDamage()
{
	return HitDamage;
}

void ARPGHitBox::SetHitDamageRelativePosition(const FVector& inNewPoation)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetRelativeLocation(inNewPoation);
	}
}

void ARPGHitBox::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);
}

void ARPGHitBox::SetBuffs(const TArray<FGameplayTag>& InBuffs)
{ 
	BuffsTags = InBuffs;
}

// Called when the game starts or when spawned
void ARPGHitBox::BeginPlay()
{
	Super::BeginPlay();

	HitDamage->OnComponentBeginOverlap.AddDynamic(this, &ARPGHitBox::HandleDamage);
}

// Called every frame
void ARPGHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ARPGHitBox::IsExist(ACharacter* InNewTaget) const
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
