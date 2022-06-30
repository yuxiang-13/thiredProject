// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_DemageNumber.h"

void UUI_DemageNumber::NativeConstruct()
{
	Super::NativeConstruct();

	PlayWidgetAnim(TEXT("FadeAnimation"));
}

void UUI_DemageNumber::UpdateDemage(const FText & InText)
{
	DamageNum->SetText(InText);
}
