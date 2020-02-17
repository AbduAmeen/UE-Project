// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTrackingTarget.h"
#include "BaseTrackingController.h"


// Sets default values
ABaseTrackingTarget::ABaseTrackingTarget()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	Health = -1;
	MagazineCount = 0;
	AmmoTotal = 0;
	bShouldFireBack = false;
	Speed = 1;
}

// Called when the game starts or when spawned
void ABaseTrackingTarget::BeginPlay()
{
	Super::BeginPlay();
}


void ABaseTrackingTarget::SetHealth(int32 health)
{
	Health = health;
}

void ABaseTrackingTarget::SetFireBack(bool lol)
{
	bShouldFireBack = lol;
}

void ABaseTrackingTarget::SetMagCount(int32 count)
{
	MagazineCount = count;
}

void ABaseTrackingTarget::SetAmmoTotal(int32 total)
{
	AmmoTotal = total;
}

void ABaseTrackingTarget::SetSpeed(float speed)
{
	Speed = speed;
}
