// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameMode.h"
#include "Options.h"
#include "MainMenuWidget.h"
#include "MainMenu.generated.h"


/**
 * 
 */
UCLASS()
class LEARNING_API AMainMenu : public AGameModeBase
{
	GENERATED_BODY()

	void BeginPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Menu")
		TSubclassOf<UUserWidget> MenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Menu")
		TSubclassOf<AGameMode> TrackingClass;
	UPROPERTY(EditDefaultsOnly, Category = "Menu")
		TSubclassOf<AGameMode> FlickingClass;
	UPROPERTY(EditDefaultsOnly, Category = "Menu")
		TSubclassOf<UOptions> OptionsClass;
	UPROPERTY()
		UOptions* Options;
	UPROPERTY()
		UMainMenuWidget* MainMenuWidget;
};
