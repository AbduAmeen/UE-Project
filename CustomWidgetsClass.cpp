// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomWidgetsClass.h"
#include "Engine/Engine.h"

bool UCustomWidgetsClass::Initialize()
{
	if (!Super::Initialize())
		return false;

	GameInstance = Cast<UTheGameInstance>(GetGameInstance());
	if (RedSlider != nullptr && BlueSlider != nullptr && GreenSlider != nullptr && AlphaSlider != nullptr)
	{
		RedSlider->SliderBarColor = FColor::Red;
		GreenSlider->SliderBarColor = FColor::Green;
		BlueSlider->SliderBarColor = FColor::Blue;
		AlphaSlider->SliderBarColor = FColor::White;

		RedSlider->SetStepSize(0.01);
		GreenSlider->SetStepSize(0.01);
		BlueSlider->SetStepSize(0.01);
		AlphaSlider->SetStepSize(0.01);

		RedSlider->OnValueChanged.AddDynamic(this, &UCustomWidgetsClass::ValueChangedRedSlider);
		BlueSlider->OnValueChanged.AddDynamic(this, &UCustomWidgetsClass::ValueChangedBlueSlider);
		GreenSlider->OnValueChanged.AddDynamic(this, &UCustomWidgetsClass::ValueChangedGreenSlider);
		AlphaSlider->OnValueChanged.AddDynamic(this, &UCustomWidgetsClass::ValueChangedAlphaSlider);

		if (GameInstance != nullptr)
		{
			RedSlider->SetValue(GameInstance->ColorOfCrosshair.R);
			GreenSlider->SetValue(GameInstance->ColorOfCrosshair.G);
			BlueSlider->SetValue(GameInstance->ColorOfCrosshair.B);
			AlphaSlider->SetValue(GameInstance->ColorOfCrosshair.A);

			PrintValue(RedValue, ChangeToInt(GameInstance->ColorOfCrosshair.R));
			PrintValue(BlueValue, ChangeToInt(GameInstance->ColorOfCrosshair.B));
			PrintValue(GreenValue, ChangeToInt(GameInstance->ColorOfCrosshair.G));
			PrintValueAlpha(AlphaValue, GameInstance->ColorOfCrosshair.A);
		}
	}
	return true;
}

int32 UCustomWidgetsClass::ChangeToInt(float number)
{

	float x = number * 255;
	return static_cast<int32>(x);
}

void UCustomWidgetsClass::PrintValue(UTextBlock* block, int32 value)
{
	if (block != nullptr)
	{
		FString lol = FString::SanitizeFloat(value);
		int32 hope;

		lol.FindChar('.', hope);
		lol.RemoveAt(hope, 2);
		block->SetText(FText::FromString(lol));
	}
}

void UCustomWidgetsClass::PrintValueAlpha(UTextBlock* block, float number)
{
	if (block != nullptr)
	{
		FString lol = FString::SanitizeFloat(number, 0);
		block->SetText(FText::FromString(lol));
	}
}

void UCustomWidgetsClass::ValueChangedRedSlider(float value)
{
	GameInstance->SetCrosshairColorRed(value);
	PrintValue(RedValue, ChangeToInt(value));
}

void UCustomWidgetsClass::ValueChangedBlueSlider(float value)
{
	GameInstance->SetCrosshairColorBlue(value);
	PrintValue(BlueValue, ChangeToInt(value));
}

void UCustomWidgetsClass::ValueChangedGreenSlider(float value)
{
	GameInstance->SetCrosshairColorGreen(value);
	PrintValue(GreenValue, ChangeToInt(value));
}

void UCustomWidgetsClass::ValueChangedAlphaSlider(float value)
{
	GameInstance->SetCrosshairColorAlpha(value);
	PrintValueAlpha(AlphaValue, value);
}

