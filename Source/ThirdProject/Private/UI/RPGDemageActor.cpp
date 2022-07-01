// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGDemageActor.h"

#include "Components/WidgetComponent.h"
#include "UI/UI_DemageNumber.h"

// Sets default values
ARPGDemageActor::ARPGDemageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamgeWidget"));

}

void ARPGDemageActor::UpdateDamgeNum(const FText& InText)
{
	// if (UUI_DemageNumber* Damage = Cast<UUI_DemageNumber>(DamageWidget->GetUserWidgetObject()))
	// {
	// 	Damage->UpdateDemage(InText);
	// }
}

// Called when the game starts or when spawned
void ARPGDemageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGDemageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

