// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Core/Fight1Component.h"

#include "Ability/RPGAbilitySystemComponent.h"
#include "Ability/RPGGameplayAbility.h"
#include "Character/Core/PGCharacterBase.h"
#include "GamePlay/RPGGameState.h"

// Sets default values for this component's properties
UFight1Component::UFight1Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFight1Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	PGCharacterBase = Cast<APGCharacterBase>(GetOwner());
	if (IsValid(PGCharacterBase))
	{
		AbilitySystemComponent = Cast<URPGAbilitySystemComponent>(PGCharacterBase->GetAbilitySystemComponent());
	}

	if (ARPGGameState* GameState = GetWorld()->GetGameState<ARPGGameState>())
	{
		TArray<UGameplayAbility*> Abilitys = GameState->GetCharacterSkills(1);
		RegisterGameAbility(Abilitys);
	}
}


// Called every frame
void UFight1Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFight1Component::ActiveSkill(FGameplayTag SkillName)
{
	if (IsValid(AbilitySystemComponent))
	{
		if (const FGameplayAbilitySpecHandle* Handle = Skills.Find(FName(*SkillName.ToString())))
		{
			AbilitySystemComponent->TryActivateAbility(*Handle);
		}
	}
}


FGameplayAbilitySpecHandle UFight1Component::RegisterGameAbility(TArray<UGameplayAbility*> InAbilites)
{
	if (IsValid(AbilitySystemComponent) && InAbilites.Num() > 0)
	{
		for(auto &Temp: InAbilites)
		{
			// 向GAS系统 添加一个能力 GiveAbility 拿到 handle
			FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Temp));
			// 拿到技能tag
			const FString string = Temp->AbilityTags.ToStringSimple();
			//转成 fName 存到 map内

			
			Skills.Add(FName(string), Handle) ;
		}
	}
	return FGameplayAbilitySpecHandle();
}

