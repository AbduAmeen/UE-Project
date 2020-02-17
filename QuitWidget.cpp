// Fill out your copyright notice in the Description page of Project Settings.

#include "QuitWidget.h"

void UQuitWidget::Canceled()
{
	SetVisibility(ESlateVisibility::Collapsed);
	PreviousMenu->SetVisibility(ESlateVisibility::Visible);
	PreviousMenu->SetKeyboardFocus();
	RemoveFromParent();
}

void UQuitWidget::Confirmed()
{
	SetVisibility(ESlateVisibility::Collapsed);
	RemoveFromParent();
	OnConfirm.Broadcast();
}

bool UQuitWidget::Initialize()
{
	if (Super::Initialize())
	{
		CancelButton->OnClicked.AddDynamic(this, &UQuitWidget::Canceled);
		ConfirmButton->OnClicked.AddDynamic(this, &UQuitWidget::Confirmed);
		SetVisibility(ESlateVisibility::Visible);
		return true;
	}
	return false;
}
