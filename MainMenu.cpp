// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainMenu::BeginPlay()
{
	APlayerController* Character = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (MenuClass != nullptr)
	{
		if (MainMenuWidget == nullptr)
		{
			MainMenuWidget = Cast<UMainMenuWidget>(CreateWidget(GetWorld(), MenuClass));
			MainMenuWidget->AddToViewport();
		}

		if (Options == nullptr)
		{
			Options = Cast<UOptions>(CreateWidget(GetWorld(), OptionsClass));
			Options->AddToViewport();
			Options->SetVisibility(ESlateVisibility::Collapsed);
		}

		MainMenuWidget->OptionsPtr = Options;
		Options->SetVisibility(ESlateVisibility::Collapsed);
		Options->MenuPtr = MainMenuWidget;
	}
	Character->bShowMouseCursor = true;
	Super::BeginPlay();	
}

