// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrackingTarget.h"
#include "GameFramework/GameMode.h"
#include "Options.h"
#include "PauseMenu.h"
#include "TrackingGamemode.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ATrackingGamemode : public AGameMode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABaseTrackingTarget> TrackingClass;
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
		TSubclassOf<UUserWidget> CrosshairClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UOptions> OptionsClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UPauseMenu> PauseMenuClass;

	UPROPERTY()
		UUserWidget* AccuracyPtr;
	UPROPERTY()
		UTheGameInstance* GameInstance;
	UPROPERTY()
		UUserWidget* CrosshairPtr;
	UPROPERTY()
		UPauseMenu* PauseMenuPtr;
	UPROPERTY()
		UOptions* OptionsPtr;
	UPROPERTY()
		float SpeedOfTarget;
	UPROPERTY()
		int32 HealthOfTarget;
	UPROPERTY()
		int32 MagSize;
	UPROPERTY()
		int32 AmmoPool;
	UPROPERTY()
		FVector Scale;
	UPROPERTY()
		bool bHeadshotEnabled;
	UPROPERTY()
		int32 NumOfTargets;

public:
	ATrackingGamemode();
	void StartPlay() override;
	void SpawnTargets(int32 numoftarget);
	UPauseMenu* CreateMenu();
	void DestroyMenu(UPauseMenu* menu);
};
