// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "Components/ActorComponent.h"
#include "Fight1Component.generated.h"


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
};
