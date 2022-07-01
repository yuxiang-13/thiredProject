// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlay/RPGHUD.h"
#include "UI/RPGDemageActor.h"

namespace RPGUtils
{
	void SpawnDanageNum ( AActor* InActor,float DamgeNum)
	{
		if(InActor)
		{
			//判定是在客户端了
			if (ARPGHUD* InHud = Cast<ARPGHUD>(InActor->GetWorld()->GetFirstPlayerController()->GetHUD()))
			{
				if (InHud->DemageNumberclass)
				{
					AActor* SpawnActor = InActor->GetWorld()->SpawnActor<AActor>(InHud->DemageNumberclass, InActor->GetActorLocation(), FRotator::ZeroRotator);
					Cast<ARPGDemageActor>(SpawnActor)->UpdateDamgeNum(FText::FromString (FString::SanitizeFloat(DamgeNum)));
				}
			}
		}
	}
};
