// Fill out your copyright notice in the Description page of Project Settings.
#include "CrosshairPreview.h"
#include "WidgetBlueprintLibrary.h"

void UCrosshairPreview::CreateCrosshair()
{
	if (GameInstance != nullptr)
	{
		GetProperties();
	}
	
	Image1->SetColorAndOpacity(Color);
	Image2->SetColorAndOpacity(Color);
	Image3->SetColorAndOpacity(Color);
	Image4->SetColorAndOpacity(Color);

	Image1->SetBrushSize(FVector2D(198 * Dimensions.X + 2, 198 * Dimensions.Y + 2));
	Image2->SetBrushSize(FVector2D(198 * Dimensions.Y + 2, 198 * Dimensions.X + 2));
	Image3->SetBrushSize(FVector2D(198 * Dimensions.X + 2, 198 * Dimensions.Y + 2));
	Image4->SetBrushSize(FVector2D(198 * Dimensions.Y + 2, 198 * Dimensions.X + 2));

	Image1->SetRenderTranslation(FVector2D(0,CenterGap * 200));
	Image2->SetRenderTranslation(FVector2D(CenterGap * 200, 0));
	Image3->SetRenderTranslation(FVector2D(0, CenterGap * -200));
	Image4->SetRenderTranslation(FVector2D(CenterGap * -200, 0));
}

void UCrosshairPreview::GetProperties()
{
	Color =GameInstance->ColorOfCrosshair;
	CenterGap = GameInstance->CenterGap;
	Dimensions = GameInstance->CrosshairDimensions;
	bDot = GameInstance->bDot;
}

bool UCrosshairPreview::Initialize()
{
	if (Super::Initialize())
	{
		GameInstance = Cast<UTheGameInstance>(GetGameInstance());
		
		if(GameInstance == nullptr)
		{
			Color = FLinearColor(1, 1, 1, 1);
			CenterGap = 5;
			Dimensions = FVector2D(10, 40);
		}
		return true;
	}
	return false;
}

void UCrosshairPreview::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	CreateCrosshair();
}



