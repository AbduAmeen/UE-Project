// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "Button.h"
#include "TheGameInstance.h"
#include "Options.h"
#include "QuitWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UQuitWidget> QuitWidgetClass;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* Options;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* ReturnToMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* QuitToDesktop;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* ResumeButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* RestartButton;
	UPROPERTY(BlueprintReadWrite)
	UOptions* OptionsPtr;
	UPROPERTY(BlueprintReadWrite)
		UQuitWidget* QuitWidgetPtr;
public:
	virtual bool Initialize() override;
	UFUNCTION()
		void ReturnToMainMenu();
	UFUNCTION()
		void ReturnToMainMenudele();
	UFUNCTION()
		void OpenOptions();
	UFUNCTION()
		void QuitToTheDesktop();
	UFUNCTION()
		void SetSettings(FUpdatedPlayerSettings settings);
	UFUNCTION()
		void QuitToTheDesktopdele();
	UFUNCTION()
		void BackWrapper();
	UFUNCTION()
		void Restart();
	bool Back();

	UTheGameInstance* GameInstance;
};
