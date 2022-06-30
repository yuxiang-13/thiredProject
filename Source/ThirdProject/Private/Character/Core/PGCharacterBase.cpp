// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Core/PGCharacterBase.h"

#include "AttributeSet.h"
#include "Ability/MyAttributeSet.h"
#include "Ability/RPGAbilitySystemComponent.h"
#include "UI/UI_EnemyHealthBar.h"

// Sets default values
APGCharacterBase::APGCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyHealthyBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthyBar"));
	EnemyHealthyBar->SetupAttachment(RootComponent);
	EnemyHealthyBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	// 初始化 能力组件
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);


	RPGAttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("RPGAttributeSet"));
}

void APGCharacterBase::HandleHealthChanged(float InHealthPercent)
{
	if (EnemyHealthyBar)
	{
		if (UUI_EnemyHealthBar* HealthyBar = Cast<UUI_EnemyHealthBar>(EnemyHealthyBar->GetUserWidgetObject()))
		{
			HealthyBar->SetHealthBarPercent(InHealthPercent);
		}
	}
}

// Called when the game starts or when spawned
void APGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 构建 属性数组,把 属性类塞进去
	TArray<UAttributeSet*> RPGAttributeSets;
	RPGAttributeSets.Add(RPGAttributeSet) ;
	AbilitySystemComponent->SetSpawnedAttributes(RPGAttributeSets);

	HandleHealthChanged(RPGAttributeSet->GetHealth() / RPGAttributeSet->GetMaxHealth());
}

// Called every frame
void APGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
