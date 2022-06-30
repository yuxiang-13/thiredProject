// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/UI_Main.h"
#include "RPGHUD.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECT_API ARPGHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	ARPGHUD();
	
public:
	UPROPERTY()
	TSubclassOf<class UUI_Main> GameMainclass;

	UPROPERTY()
	TSubclassOf<class AActor> DemageNumberclass;

private:
	class UUI_Main* GameMain;
};
