// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGDemageActor.generated.h"

UCLASS()
class THIRDPROJECT_API ARPGDemageActor : public AActor
{
	GENERATED_BODY()
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UWidgetComponent* DamageWidget;

public:	
	// Sets default values for this actor's properties
	ARPGDemageActor();
	
	void UpdateDamgeNum(const FText& 工nText);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
