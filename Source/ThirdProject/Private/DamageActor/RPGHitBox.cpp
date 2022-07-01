// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor/RPGHitBox.h"

#include "Components/BoxComponent.h"

ARPGHitBox::ARPGHitBox(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HitCollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	HitDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(HitCollisionRootComponent);

	// 存活周期
	InitialLifeSpan = 4.0f;
	// 
}

void ARPGHitBox::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

UPrimitiveComponent* ARPGHitBox::GetHitDamage()
{
}

void ARPGHitBox::SetHitDamageRelativePosition()
{
}

void ARPGHitBox::SetBoxExtent(const FVector& InNewBoxExtent)
{
}

// Called when the game starts or when spawned
void ARPGHitBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

