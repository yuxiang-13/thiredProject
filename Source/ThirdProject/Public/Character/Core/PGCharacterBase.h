// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "PGCharacterBase.generated.h"


UCLASS()
class THIRDPROJECT_API APGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	//1 引入 GAS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class URPGAbilitySystemComponent* AbilitySystemComponent;


	// 属性
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UMyAttributeSet* RPGAttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=RPGCharacterBase)
	class UWidgetComponent* EnemyHealthyBar;

	// 战斗组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=RPGCharacterBase)
	class UFight1Component* FightComponent;

public:
	// Sets default values for this character's properties
	APGCharacterBase();

	virtual void HandleHealthChanged(float InHealthPercent) ;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
	URPGAbilitySystemComponent* GetAbilitySystemComponent();
	
	
	UFUNCTION(BlueprintCallable)
	void ActiveSkill(FGameplayTag SkillName);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
