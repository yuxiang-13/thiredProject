// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "Components/ActorComponent.h"
#include "ThirdProject/ThirdProjectCharacter.h"


#include "Fight1Component.generated.h"


USTRUCT(BlueprintType)
struct FComboCheck
{
	GENERATED_USTRUCT_BODY()


	// 连击
	UPROPERTY(EditDefaultsOnly, Category = Comb)
		int32 ComboIndex;

	// 短按
	UPROPERTY(EditDefaultsOnly, Category = Comb)
		int32 bLongPress;

	// 长按
	UPROPERTY(EditDefaultsOnly, Category = Comb)
		int32 bShortPress;

	// 回调 GA 普通攻击
	class AThirdProjectCharacter* Character;

	UPROPERTY()
		int32 MaxIndex;

	// 连击名字
	UPROPERTY()
		FName ComboKey;

	FComboCheck()
	{
		ComboIndex = -1;
		bLongPress = bShortPress = false;
		Character = nullptr;
		MaxIndex = 0;
	};

	
	//鼠标 按下
	void Press()
	{
		// 第一次按下
		if (ComboIndex == -1 && Character)
		{
			ComboIndex++;
			check(Character);
		}

		if (Character)
		{
			// 激活技能
			Character->ActiveSkillByName(FString("Character.Skill.ComboAttack"));
		}

		bLongPress = bShortPress = true;
	};
	
	//鼠标 松开
	void Releeased()
	{
		bLongPress = false;
		
	};
	
	// 动画结束
	void Reset()
	{
		ComboIndex = -1;
	};
	
	// 每次播放 引导到 下一个动作索引
	void UpdateComboIndex()
	{
		ComboIndex++;
		if (ComboIndex > MaxIndex)
		{
			ComboIndex = 1;
		}
	};
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPROJECT_API UFight1Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY()
		class APGCharacterBase* PGCharacterBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
		class URPGAbilitySystemComponent* AbilitySystemComponent;
	
	TMap<FName, FGameplayAbilitySpecHandle> Skills;
	
	UPROPERTY()
	FComboCheck ComboCheck;
public:	
	// Sets default values for this component's properties
	UFight1Component();

	FGameplayAbilitySpecHandle RegisterGameAbility(TArray<UGameplayAbility*> InAbilites);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ActiveSkill(FGameplayTag SkillName);
	void ActiveSkill(FString SkillName);

	// combo连击
	void ComboAttackOnPressed();
	void ComboAttackOnReleased();
	void ResetComboCheck();
	

	FORCEINLINE FComboCheck* GetComboCheck() { return &ComboCheck; };
};
