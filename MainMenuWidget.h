// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "Options.h"
#include "TheGameInstance.h"
#include "Button.h"
#include "QuitWidget.h"
#include "MainMenuWidget.generated.h"


/**
 * 
 */
UCLASS()
class LEARNING_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UOptions> OptionsWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UQuitWidget> QuitWidgetClass;
	UPROPERTY()
		UTheGameInstance* GameInstance;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* QuitGameButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* TrackingButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* FlickingButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* OptionsButton;
	UPROPERTY()
		UOptions* OptionsPtr;
	UPROPERTY()
		UQuitWidget* QuitWidgetPtr;
public:
	UFUNCTION()
	virtual bool Initialize() override;
	UFUNCTION()
		void QuitGame();
	UFUNCTION()
		void OpenOptions();
	UFUNCTION()
		void FlickingButtonEvent();
	UFUNCTION()
		void TrackingButtonEvent();
	UFUNCTION()
		void QuitGamedele();
};
