// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "GameFramework/GameMode.h"

bool UPauseMenu::Initialize()
{
	if (!Super::Initialize()) { return false; }

	GameInstance = Cast<UTheGameInstance>(GetGameInstance());
	
	if (ReturnToMenu != nullptr && QuitToDesktop != nullptr && Options != nullptr)
	{
		ReturnToMenu->OnClicked.AddDynamic(this, &UPauseMenu::ReturnToMainMenu);
		Options->OnClicked.AddDynamic(this, &UPauseMenu::OpenOptions);
		QuitToDesktop->OnClicked.AddDynamic(this, &UPauseMenu::QuitToTheDesktop);
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::BackWrapper);
		RestartButton->OnClicked.AddDynamic(this, &UPauseMenu::Restart);
	}
	return true;
}

void UPauseMenu::ReturnToMainMenu()
{
	QuitWidgetPtr = CreateWidget<UQuitWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), QuitWidgetClass);
	QuitWidgetPtr->AddToViewport();
	QuitWidgetPtr->PreviousMenu = this;
	QuitWidgetPtr->OnConfirm.AddUFunction(this, FName("ReturnToMainMenudele"));
	QuitWidgetPtr->SetKeyboardFocus();
}

void UPauseMenu::ReturnToMainMenudele()
{
	RemoveFromParent();
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu_Map");
}

void UPauseMenu::OpenOptions()
{
	if (OptionsPtr != nullptr)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		OptionsPtr->SetVisibility(ESlateVisibility::Visible);
		OptionsPtr->MenuPtr = this;
		OptionsPtr->OnSettingChanged.AddUFunction(this,FName("SetSettings"));
		OptionsPtr->SetKeyboardFocus();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "Please restart the game");
	}
}

void UPauseMenu::QuitToTheDesktop()
{
	QuitWidgetPtr = CreateWidget<UQuitWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), QuitWidgetClass);
	QuitWidgetPtr->AddToViewport();
	QuitWidgetPtr->PreviousMenu = this;
	QuitWidgetPtr->OnConfirm.AddUFunction(this, FName("QuitToTheDesktopdele"));
	QuitWidgetPtr->SetKeyboardFocus();
}

void UPauseMenu::SetSettings(FUpdatedPlayerSettings settings)
{
	AMyPlayerController* Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	AMyCharacter* Character = Cast<AMyCharacter>(Controller->GetPawn());

	if (Controller != nullptr)
	{
		Controller->SetMode(settings.SensitivityMode);
		Controller->FOV(settings.FOV);
	}

	if (Character != nullptr)
	{
		Character->GetTheCamera()->SetFieldOfView(settings.FOV);
		if (Character->bHidden != settings.hideplayer)
		{
			Character->SetActorHiddenInGame(settings.hideplayer);
		}
	}
}

void UPauseMenu::QuitToTheDesktopdele()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UPauseMenu::BackWrapper()
{
	if (!Back())
	{
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AMyCharacter* Character = Cast<AMyCharacter>(Controller->GetPawn());
		Character->MenuControls(false);
		Controller->SetInputMode(FInputModeGameOnly());
		Controller->bShowMouseCursor = false;
		Controller->SetPause(false);
	}
}

void UPauseMenu::Restart()
{
	AGameMode* Gamemode = Cast<AGameMode>(GetWorld()->GetAuthGameMode());

	if (Gamemode != nullptr)
	{
		Gamemode->RestartGame();
	}
}

bool UPauseMenu::Back()
{
	if (QuitWidgetPtr != nullptr)
	{
		if (QuitWidgetPtr->IsVisible())
		{
			QuitWidgetPtr->Canceled();
			return true;
		}
	}

	if (OptionsPtr != nullptr)
	{
		if (OptionsPtr->IsVisible())
		{
			OptionsPtr->Cancel();
			return true;
		}
	}
	
	SetVisibility(ESlateVisibility::Collapsed);
	return false;
}

