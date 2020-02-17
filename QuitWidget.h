// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "QuitWidget.generated.h"

/**
 * 
 */
DECLARE_EVENT(UQuitWidget, FConfirm)

UCLASS()
class LEARNING_API UQuitWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FConfirm OnConfirm;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* CancelButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* ConfirmButton;
	UPROPERTY()
		UUserWidget* PreviousMenu;
public:
	UFUNCTION()
		void Canceled();
	UFUNCTION()
		void Confirmed();
	UFUNCTION()
		virtual bool Initialize() override;
	
};
