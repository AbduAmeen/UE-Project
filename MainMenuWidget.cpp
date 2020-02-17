// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "GenericPlatformMisc.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameMode.h"
#include "QuitWidget.h"

bool UMainMenuWidget::Initialize()
{
	if (Super::Initialize())
	{
		GameInstance = Cast<UTheGameInstance>(GetGameInstance());
		
		if (GameInstance != nullptr)
		{
			QuitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
			OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenOptions);
			FlickingButton->OnClicked.AddDynamic(this, &UMainMenuWidget::FlickingButtonEvent);
			TrackingButton->OnClicked.AddDynamic(this, &UMainMenuWidget::TrackingButtonEvent);
			SetKeyboardFocus();
			return true;
		}
	}
	return false;
}

void UMainMenuWidget::QuitGame()
{
	QuitWidgetPtr = CreateWidget<UQuitWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), QuitWidgetClass);
	QuitWidgetPtr->AddToViewport();
	QuitWidgetPtr->PreviousMenu = this;
	QuitWidgetPtr->OnConfirm.AddUFunction(this, FName("QuitGamedele"));
	QuitWidgetPtr->SetKeyboardFocus();
}

void UMainMenuWidget::OpenOptions()
{
	OptionsPtr->SetVisibility(ESlateVisibility::Visible);
	SetVisibility(ESlateVisibility::Collapsed);
	OptionsPtr->SetKeyboardFocus();
}

void UMainMenuWidget::FlickingButtonEvent()
{
	RemoveFromParent();
	UGameplayStatics::OpenLevel(GetWorld(), "Tutorial_Map");
}

void UMainMenuWidget::TrackingButtonEvent()
{
	RemoveFromParent();
	UGameplayStatics::OpenLevel(GetWorld(), "Tracking_Map");
}

void UMainMenuWidget::QuitGamedele()
{
	FGenericPlatformMisc::RequestExit(false);
}
	