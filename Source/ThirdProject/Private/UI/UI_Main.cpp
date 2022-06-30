// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_Main.h"

#include "Components/ProgressBar.h"

UUI_Main::UUI_Main()
{
}

void UUI_Main::UpdateHealthProgress(float InPercent)
{
	Health->SetPercent(InPercent);
}

void UUI_Main::UpdateManaProgress(float InPercent)
{
	Mana->SetPercent(InPercent);
}

void UUI_Main::UpdateStaminaProgress(float InPercent)
{
	stamina->SetPercent(InPercent);
}
