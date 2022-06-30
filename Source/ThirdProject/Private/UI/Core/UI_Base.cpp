// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Core/UI_Base.h"

void UUI_Base::PlayWidgetAnim(const FString& InAnimName)
{
	if (UWidgetAnimation* TempAnimation = GetNameWidgetAnimation(InAnimName))
	{
		PlayAnimation(TempAnimation);
	}
}

// 查找 动画
UWidgetAnimation* UUI_Base::GetNameWidgetAnimation(const FString& InWigetName)
{
	if(UWidgetBlueprintGeneratedClass* WidgetBlueprintCenerated = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		TArray<UWidgetAnimation*> TArrayAnimations = WidgetBlueprintCenerated->Animations;

		// 查找
		UWidgetAnimation ** TempAnim =  TArrayAnimations.FindByPredicate(
			[&](const UWidgetAnimation* OurAnimation)
			{
				return OurAnimation->GetFName().ToString() == InWigetName + FString("_INST");
			}
		);

		return *TempAnim;
	}
	return nullptr;
}
