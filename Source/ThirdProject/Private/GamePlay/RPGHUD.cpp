// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/RPGHUD.h"

void ARPGHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (GameMainclass)
	{
		GameMain = CreateWidget<UUI_Main>(GetWorld(), GameMainclass);
		GameMain->AddToViewport();
	}
}

void ARPGHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

ARPGHUD::ARPGHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_Main> GameMain_BPClass(TEXT("WidgetBlueprint'/Game/UI/Game/BP_MainUI.BP_MainUI_C'"));
	GameMainclass = GameMain_BPClass.Class;
}
