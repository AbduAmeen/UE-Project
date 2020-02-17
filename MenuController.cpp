// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuController.h"
#include "WidgetBlueprintLibrary.h"
#include "MainMenu.h"

void AMenuController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
	AMainMenu* Gamemode = Cast<AMainMenu>(GetWorld()->GetAuthGameMode());
	UMainMenuWidget* widget = Gamemode->MainMenuWidget;

	widget->SetKeyboardFocus();
}

void AMenuController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("EscapeKey", IE_Pressed, this, &AMenuController::Back);
	InputComponent->BindAction("Enter", IE_Pressed, this, &AMenuController::Enter);
}

void AMenuController::Back()
{
	AMainMenu* Gamemode = Cast<AMainMenu>(GetWorld()->GetAuthGameMode());
	UMainMenuWidget* widget = Gamemode->MainMenuWidget;

	if (widget->QuitWidgetPtr != nullptr)
	{
		if (widget->QuitWidgetPtr->IsVisible())
		{
			widget->QuitWidgetPtr->Canceled();
		}
	}

	if (widget->OptionsPtr != nullptr)
	{
		if (widget->OptionsPtr->IsVisible())
		{
			widget->OptionsPtr->Cancel();
		}
	}
}

void AMenuController::Enter()
{
	AMainMenu* Gamemode = Cast<AMainMenu>(GetWorld()->GetAuthGameMode());
	UMainMenuWidget* widget = Gamemode->MainMenuWidget;

	if (widget->QuitWidgetPtr != nullptr)
	{
		if (widget->QuitWidgetPtr->IsVisible())
		{
			widget->QuitWidgetPtr->Confirmed();
		}
	}
}

