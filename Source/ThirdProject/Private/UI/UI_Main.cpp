// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_Main.h"

#include "Components/ProgressBar.h"
#include "ThirdProject/ThirdProjectCharacter.h"

UUI_Main::UUI_Main(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer), TargetHealth(1.0f)
{
}

void UUI_Main::NativeConstruct()
{
	Super::NativeConstruct();

	if (AThirdProjectCharacter* PlayerCharacter = Cast<AThirdProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		PlayerCharacter->UpdateHealthProgress.BindUObject(this, &UUI_Main::UpdateHealthProgress);
		PlayerCharacter->UpdateManaProgress.BindUObject(this, &UUI_Main::UpdateManaProgress);
		PlayerCharacter->UpdateStanProgress.BindUObject(this, &UUI_Main::UpdateStaminaProgress);
	}

}

void UUI_Main::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_Main::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// 近似不相等
	if (Health && !FMath::IsNearlyEqual(TargetHealth,Health->Percent))
	{
		double fInterpTo = FMath::FInterpTo(Health->Percent, TargetHealth, InDeltaTime, 3.0);
		Health->SetPercent (fInterpTo);
	}
}

void UUI_Main::UpdateHealthProgress(float InPercent)
{
	// Health->SetPercent(InPercent);
	TargetHealth = InPercent;
	
}


void UUI_Main::UpdateManaProgress(float InPercent)
{
	Mana->SetPercent(InPercent);
}

void UUI_Main::UpdateStaminaProgress(float InPercent)
{
	stamina->SetPercent(InPercent);
}
