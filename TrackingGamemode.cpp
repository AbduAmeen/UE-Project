// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackingGamemode.h"
#include "BaseTrackingTarget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "MyPlayerController.h"
#include "UserWidget.h"
#include "Options.h"
#include "PauseMenu.h"

ATrackingGamemode::ATrackingGamemode()
{
	HealthOfTarget = 0;
	SpeedOfTarget = 0;
	MagSize = 0;
	AmmoPool = 0;
	Scale = FVector(1, 1, 1);
	bHeadshotEnabled = false;
	NumOfTargets = 1;
}

void ATrackingGamemode::StartPlay()
{
	Super::StartPlay();
	
	AMyPlayerController* Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PauseMenuPtr = Cast<UPauseMenu>(CreateWidget(Controller, PauseMenuClass));
	OptionsPtr = Cast<UOptions>(CreateWidget(Controller, OptionsClass));

	GameInstance = Cast<UTheGameInstance>(GetWorld()->GetGameInstance());

	if (Controller != nullptr)
	{
		Controller->SetInputMode(FInputModeGameOnly());

		if (CrosshairClass != nullptr)
		{
			CrosshairPtr = CreateWidget<UUserWidget>(GetWorld(), CrosshairClass);
			CrosshairPtr->AddToViewport();
		}

		if (PauseMenuPtr != nullptr)
		{
			PauseMenuPtr->AddToViewport();
			PauseMenuPtr->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (OptionsPtr != nullptr)
		{
			OptionsPtr->AddToViewport();
			OptionsPtr->SetVisibility(ESlateVisibility::Collapsed);
			OptionsPtr->MenuPtr = PauseMenuPtr;
			PauseMenuPtr->OptionsPtr = OptionsPtr;
		}
	}

	SpawnTargets(NumOfTargets);
	StartMatch();
}

void ATrackingGamemode::SpawnTargets(int32 numoftarget)
{
	FVector middle(160, 108, 195);
	FActorSpawnParameters Params;
	FString string = "Target";
	

	for (int32 i = 0; i < numoftarget; i++)
	{
		string.AppendInt(i);
		FName name = FName(*string);
		Params.Name = name;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		ABaseTrackingTarget* Character = GetWorld()->SpawnActor<ABaseTrackingTarget>(TrackingClass, middle, FRotator(0, 0, 0), Params);

		Character->SetHealth(HealthOfTarget);
		Character->SetActorRelativeScale3D(Scale);
		Character->SetSpeed(SpeedOfTarget);
		Character->SetAmmoTotal(AmmoPool);
		Character->SetMagCount(MagSize);
	}
}

UPauseMenu* ATrackingGamemode::CreateMenu()
{
	PauseMenuPtr->SetVisibility(ESlateVisibility::Visible);
	return PauseMenuPtr;
}

void ATrackingGamemode::DestroyMenu(UPauseMenu* menu)
{
	menu->SetVisibility(ESlateVisibility::Collapsed);
	menu = nullptr;
}
