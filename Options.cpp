// Fill out your copyright notice in the Description page of Project Settings.

#include "Options.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


void UOptions::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

bool UOptions::Initialize()
{
	if (Super::Initialize())
	{
		GameInstance = Cast<UTheGameInstance>(GetGameInstance());

		if (GameInstance != nullptr)
		{
			InitializeWidgets();
			tempstring.Empty();
			return true;
		}
	}
	return false;
}

void UOptions::InitializeWidgets()
{
	CheckIfWithin(GameInstance->ColorOfCrosshair.R, 1, 0);
	CheckIfWithin(GameInstance->ColorOfCrosshair.G, 1, 0);
	CheckIfWithin(GameInstance->ColorOfCrosshair.B, 1, 0);
	CheckIfWithin(GameInstance->ColorOfCrosshair.A, 1, 0);

	if (VerticalSensitivitySlider != nullptr && VerticalSensitivityTextBox != nullptr && VerticalMatchHorizontal != nullptr)
	{
		VerticalSensitivitySlider->OnValueChanged.AddDynamic(this, &UOptions::ValueChangedVerticalSensitivitySlider);
		VerticalSensitivityTextBox->OnTextChanged.AddDynamic(this, &UOptions::TextChangeVerticalTextBox);
		VerticalSensitivityTextBox->OnTextCommitted.AddDynamic(this, &UOptions::TextConfirmVerticalSensitivity);

		CheckIfWithin(GameInstance->Sensitivity.Y, GameInstance->Maximum, GameInstance->Minimum);
	}

	if (CenterGapSlider != nullptr && CrosshairWidthSlider != nullptr && CrosshairLengthSlider != nullptr)
	{
		CheckIfWithin(GameInstance->CenterGap, 1, 0);
		CenterGapSlider->SetValue(GameInstance->CenterGap);
		CenterGapSlider->OnValueChanged.AddDynamic(this, &UOptions::ValueChangedCenterGap);

		CheckIfWithin(GameInstance->CrosshairDimensions.X, 1, 0);
		CrosshairWidthSlider->SetValue(GameInstance->CrosshairDimensions.X);
		CrosshairWidthSlider->OnValueChanged.AddDynamic(this, &UOptions::ValueChangedCrosshairWidth);

		CheckIfWithin(GameInstance->CrosshairDimensions.Y, 1, 0);
		CrosshairLengthSlider->SetValue(GameInstance->CrosshairDimensions.Y);
		CrosshairLengthSlider->OnValueChanged.AddDynamic(this, &UOptions::ValueChangedCrosshairLength);
	}

	if (CrosshairLengthTextBox != nullptr && CrosshairWidthTextBox != nullptr && CenterGapTextBox != nullptr)
	{
		CrosshairLengthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.Y, 2,100));
		CrosshairLengthTextBox->OnTextChanged.AddDynamic(this, &UOptions::TextChangeCrosshairLength);
		CrosshairLengthTextBox->OnTextCommitted.AddDynamic(this, &UOptions::TextConfirmCrosshairLength);
		
		CrosshairWidthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.X, 2,100));
		CrosshairWidthTextBox->OnTextChanged.AddDynamic(this, &UOptions::TextChangeCrosshairWidth);
		CrosshairWidthTextBox->OnTextCommitted.AddDynamic(this, &UOptions::TextConfirmCrosshairWidth);
		
		CenterGapTextBox->SetText(FormatFloatToText(GameInstance->CenterGap,  2,100));
		CenterGapTextBox->OnTextChanged.AddDynamic(this, &UOptions::TextChangeCenterGap);
		CenterGapTextBox->OnTextCommitted.AddDynamic(this, &UOptions::TextConfirmCenterGap);
	}

	if (CancelButton != nullptr && TheWidgetSwitcher != nullptr && GameSettings != nullptr)
	{
		CancelButton->OnClicked.AddDynamic(this, &UOptions::Cancel);
		CrosshairSettings->OnClicked.AddDynamic(this, &UOptions::OpenCrosshairSettings);
		GameSettings->OnClicked.AddDynamic(this, &UOptions::OpenGameSettings);
	}

	if (FovTextBlock != nullptr && FovComboBox != nullptr && CustomFov != nullptr)
	{
		FovComboBox->OnSelectionChanged.AddDynamic(this, &UOptions::CustomFovSetting);
		CustomFov->OnTextChanged.AddDynamic(this, &UOptions::TextChangeCustomFov);
		CustomFov->OnTextCommitted.AddDynamic(this, &UOptions::TextConfirmCustomFov);

		CheckIfWithin(GameInstance->FOVOfCharacter, 150, 50);
		
		if (GameInstance->FOVOfCharacter == 90)
		{
			FovTextBlock->SetVisibility(ESlateVisibility::Collapsed);
			CustomFov->SetVisibility(ESlateVisibility::Collapsed);
			FovComboBox->SetSelectedOption(FovComboBox->GetOptionAtIndex(0));
		}
		else if (GameInstance->FOVOfCharacter == 80)
		{
			FovTextBlock->SetVisibility(ESlateVisibility::Collapsed);
			CustomFov->SetVisibility(ESlateVisibility::Collapsed);

			FovComboBox->SetSelectedOption(FovComboBox->GetOptionAtIndex(1));
		}
		else
		{
			FovComboBox->SetSelectedOption("Custom");
			CustomFov->SetText(FText::AsNumber(GameInstance->FOVOfCharacter));
		}
	}

	if (HorizontalSensitivitySlider != nullptr && HorizontalSensitivityTextBox != nullptr && SensitivityType != nullptr)
	{
		SensitivityType->OnSelectionChanged.AddDynamic(this, &UOptions::SelectionChangeSensitivityType);
		HorizontalSensitivitySlider->OnValueChanged.AddDynamic(this, &UOptions::ValueChangedHorizontalSensitivitySlider);
		HorizontalSensitivityTextBox->OnTextChanged.AddDynamic(this, &UOptions::TextChangeHorizontalTextBox);
		HorizontalSensitivityTextBox->OnTextCommitted.AddDynamic(this, &UOptions::TextConfirmHorizontalSensitivity);

		CheckIfWithin(GameInstance->Sensitivity.X, GameInstance->Maximum, GameInstance->Minimum);

		if (GameInstance->SensitivityMode == CSGO)
		{
			InitializeSensitivityWidgetHelper(CSGO, GameInstance->Maximum, GameInstance->Minimum);
		}
		else if (GameInstance->SensitivityMode == Overwatch)
		{
			InitializeSensitivityWidgetHelper(Overwatch, GameInstance->Maximum, GameInstance->Minimum);
		}
		else if (GameInstance->SensitivityMode == FortniteSlider)
		{
			InitializeSensitivityWidgetHelper(FortniteSlider, GameInstance->Maximum, GameInstance->Minimum);
		}
		else if (GameInstance->SensitivityMode == FortniteConfig)
		{
			InitializeSensitivityWidgetHelper(FortniteConfig, GameInstance->Maximum, GameInstance->Minimum);
		}
		else if (GameInstance->SensitivityMode == Rainbow6)
		{
			InitializeSensitivityWidgetHelper(Rainbow6, GameInstance->Maximum, GameInstance->Minimum);
		}
		else if (GameInstance->SensitivityMode == Apex)
		{
			InitializeSensitivityWidgetHelper(Apex, GameInstance->Maximum, GameInstance->Minimum);
		}
	}

	if (VerticalMatchHorizontal != nullptr && SaveSettingsButton != nullptr && ResetToDefaultButton != nullptr)
	{
		VerticalMatchHorizontal->OnCheckStateChanged.AddDynamic(this, &UOptions::CheckboxVerticalMatchHorizontal);
		SaveSettingsButton->OnClicked.AddDynamic(this, &UOptions::SaveSettingsDele);
		ResetToDefaultButton->OnClicked.AddDynamic(this, &UOptions::ResetToDefault);

		if (GameInstance->bSensitivityVerticalSame)
		{
			VerticalMatchHorizontal->SetCheckedState(ECheckBoxState::Checked);
		}
		else
		{
			VerticalMatchHorizontal->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}

	if (HidePlayerModelCheckbox != nullptr)
	{
		HidePlayerModelCheckbox->OnCheckStateChanged.AddDynamic(this, &UOptions::HidePlayerModel);

		if (GameInstance->bHidePlayerModel)
		{
			HidePlayerModelCheckbox->SetCheckedState(ECheckBoxState::Checked);
		}
		else
		{
			HidePlayerModelCheckbox->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}

	InitializeSettings();
}

void UOptions::SelectionChangeSensitivityType(FString string, ESelectInfo::Type type)
{
	if (string == SensitivityType->GetOptionAtIndex(0))
	{
		GameInstance->SetSensitivityMode(CSGO);
		SensitivityTypeHelper(CSGO, GameInstance->Maximum, GameInstance->Minimum, GameInstance->bSensitivityVerticalSame);
		settings.Sensitivity = GameInstance->Sensitivity;
		settings.SensitivityMode = CSGO;
		OnSettingChanged.Broadcast(settings);
	}
	else if (string == SensitivityType->GetOptionAtIndex(1))
	{
		GameInstance->SetSensitivityMode(Overwatch);
		SensitivityTypeHelper(Overwatch, GameInstance->Maximum, GameInstance->Minimum, GameInstance->bSensitivityVerticalSame);
		settings.Sensitivity = GameInstance->Sensitivity;
		settings.SensitivityMode = Overwatch;
		OnSettingChanged.Broadcast(settings);
	}
	else if (string == SensitivityType->GetOptionAtIndex(2))
	{
		GameInstance->SetSensitivityMode(FortniteSlider);
		SensitivityTypeHelper(FortniteSlider, GameInstance->Maximum, GameInstance->Minimum, GameInstance->bSensitivityVerticalSame);
		settings.Sensitivity = GameInstance->Sensitivity;
		settings.SensitivityMode = FortniteSlider;
		OnSettingChanged.Broadcast(settings);
	}
	else if (string == SensitivityType->GetOptionAtIndex(3))
	{
		GameInstance->SetSensitivityMode(FortniteConfig);
		SensitivityTypeHelper(FortniteConfig, GameInstance->Maximum, GameInstance->Minimum, GameInstance->bSensitivityVerticalSame);
		settings.Sensitivity = GameInstance->Sensitivity;
		settings.SensitivityMode = FortniteConfig;
		OnSettingChanged.Broadcast(settings);
	}
	else if (string == SensitivityType->GetOptionAtIndex(4))
	{
		GameInstance->SetSensitivityMode(Rainbow6);
		SensitivityTypeHelper(Rainbow6, GameInstance->Maximum, GameInstance->Minimum, GameInstance->bSensitivityVerticalSame);
		settings.Sensitivity = GameInstance->Sensitivity;
		settings.SensitivityMode = Rainbow6;
		OnSettingChanged.Broadcast(settings);
	}
	else if (string == SensitivityType->GetOptionAtIndex(5))
	{
		GameInstance->SetSensitivityMode(Apex);
		SensitivityTypeHelper(Apex, GameInstance->Maximum, GameInstance->Minimum, GameInstance->bSensitivityVerticalSame);
		settings.Sensitivity = GameInstance->Sensitivity;
		settings.SensitivityMode = Apex;
		OnSettingChanged.Broadcast(settings);
	}
}

void UOptions::Cancel()
{
	if (MenuPtr != nullptr)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		MenuPtr->SetVisibility(ESlateVisibility::Visible);
	}
}

void UOptions::OpenCrosshairSettings()
{
	TheWidgetSwitcher->SetActiveWidgetIndex(1);
}

void UOptions::OpenGameSettings()
{
	TheWidgetSwitcher->SetActiveWidgetIndex(0);
}

void UOptions::ValueChangedCrosshairWidth(float value)
{
	GameInstance->SetCrosshairDimensionsX(value);
	CrosshairWidthTextBox->SetText(FormatFloatToText(value, 2,200));
}

void UOptions::ValueChangedHorizontalSensitivitySlider(float value)
{
	if (GameInstance->bSensitivityVerticalSame)
	{
		if (GameInstance->SensitivityMode == CSGO)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			VerticalSensitivitySlider->SetValue(value);
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == Overwatch || GameInstance->SensitivityMode == Rainbow6)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			VerticalSensitivitySlider->SetValue(value);
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == FortniteSlider || GameInstance->SensitivityMode == FortniteConfig)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			VerticalSensitivitySlider->SetValue(value);
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == Apex)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			VerticalSensitivitySlider->SetValue(value);
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
	}
	else
	{
		if (GameInstance->SensitivityMode == CSGO)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol, -1, 1));
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == Overwatch || GameInstance->SensitivityMode == Rainbow6)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol, -1, 1));
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == FortniteSlider || GameInstance->SensitivityMode == FortniteConfig)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol, -1, 1));
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == Apex)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol, -1, 1));
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			OnSettingChanged.Broadcast(settings);
		}
	}
}

void UOptions::ValueChangedVerticalSensitivitySlider(float value)
{
	if(GameInstance->bSensitivityVerticalSame)
	{
		if (GameInstance->SensitivityMode == CSGO)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			HorizontalSensitivitySlider->SetValue(value);
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == Overwatch || GameInstance->SensitivityMode == Rainbow6)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			HorizontalSensitivitySlider->SetValue(value);
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == FortniteSlider || GameInstance->SensitivityMode == FortniteConfig)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			HorizontalSensitivitySlider->SetValue(value);
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == Apex)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			HorizontalSensitivitySlider->SetValue(value);
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			GameInstance->SetHorizontalSensitivity(lol);
			settings.Sensitivity.X = lol;
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
	}
	else
	{
		if (GameInstance->SensitivityMode == CSGO)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == Overwatch || GameInstance->SensitivityMode == Rainbow6)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == FortniteSlider || GameInstance->SensitivityMode == FortniteConfig)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
		else if (GameInstance->SensitivityMode == Apex)
		{
			float lol = (value * (GameInstance->Maximum - GameInstance->Minimum)) + GameInstance->Minimum;
			VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
			GameInstance->SetVerticalSensitivity(lol);
			settings.Sensitivity.Y = lol;
			OnSettingChanged.Broadcast(settings);
		}
	}
}

void UOptions::CheckboxVerticalMatchHorizontal(bool lol)
{
	GameInstance->SetbSensitivityVerticalSame(lol);
	settings.bVerticalSame = lol;
	
	if (GameInstance->bSensitivityVerticalSame)
	{
		FString pop = FString::SanitizeFloat(GameInstance->Sensitivity.X,0);
		settings.Sensitivity.Y = GameInstance->Sensitivity.X;
		GameInstance->SetVerticalSensitivity(GameInstance->Sensitivity.X);
		VerticalSensitivityTextBox->SetText(FText::FromString(pop));
		VerticalSensitivitySlider->SetValue(HorizontalSensitivitySlider->GetValue());
	}
	OnSettingChanged.Broadcast(settings);
}

void UOptions::SaveSettingsDele()
{
	GameInstance->SaveTheSettings();
}

void UOptions::ResetToDefault()
{
	GameInstance->ReadDefaults();
}

void UOptions::HidePlayerModel(bool lol)
{
	GameInstance->bHidePlayerModel = lol;
	settings.hideplayer = lol;
	OnSettingChanged.Broadcast(settings);
}

void UOptions::ValueChangedCrosshairLength(float value)
{
	GameInstance->SetCrosshairDimensionsY(value);
	CrosshairLengthTextBox->SetText(FormatFloatToText(float(value ), 2,200));
}

void UOptions::ValueChangedCenterGap(float value)
{
	GameInstance->SetCenterGap(value);
	CenterGapTextBox->SetText(FormatFloatToText(value,  2,100));
}

void UOptions::TextChange(UEditableTextBox* ptr,const FText& Text)
{
	if (!Text.IsEmptyOrWhitespace())
	{
		if (Text.IsNumeric())
		{
			float lol = FCString::Atof(*Text.ToString());
			tempstring = FString::SanitizeFloat(lol, 0);
			return;
		}
		ptr->SetText(FText::FromString(tempstring));
	}
	else
	{
		tempstring = Text.ToString();
	}
}

void UOptions::CheckIfWithin(float& value, float maximum, float minimum)
{
	if (value < minimum)
	{
		value = minimum;
		return;
	}

	if (value > maximum)
	{
		value = maximum;
		return;
	}
	return;
}

void UOptions::InitializeSettings()
{
	settings.Color = GameInstance->ColorOfCrosshair;
	settings.Dot = GameInstance->bDot;
	settings.Dimensions = GameInstance->CrosshairDimensions;
	settings.Gap = GameInstance->CenterGap;
	settings.FOV = GameInstance->FOVOfCharacter;
	settings.bThirdPerson = GameInstance->bThirdPersonEnabled;
	settings.bFirstPerson = GameInstance->bFirstPersonEnabled;
	settings.bVerticalSame = GameInstance->bSensitivityVerticalSame;
	settings.hideplayer = GameInstance->bHidePlayerModel;
	settings.SensitivityMode = GameInstance->SensitivityMode;
	settings.Sensitivity = GameInstance->Sensitivity;
}

void UOptions::TextChangeCrosshairLength(const FText& Text)
{
	TextChange(CrosshairLengthTextBox,Text);
}

void UOptions::TextChangeCrosshairWidth(const FText& Text)
{
	TextChange(CrosshairWidthTextBox, Text);
}

void UOptions::TextChangeCenterGap(const FText& Text)
{
	TextChange(CenterGapTextBox, Text);
}

void UOptions::TextChangeCustomFov(const FText& Text)
{
	TextChange(CustomFov,Text);
}

void UOptions::TextChangeVerticalTextBox(const FText& Text)
{
	TextChange(VerticalSensitivityTextBox,Text);
}

void UOptions::TextChangeHorizontalTextBox(const FText& Text)
{
	TextChange(HorizontalSensitivityTextBox,Text);
}

void UOptions::TextConfirmCustomFov(const FText& Text, ETextCommit::Type type)
{
	FString string = Text.ToString();

	if (!Text.IsEmptyOrWhitespace())
	{
		if (string.IsNumeric())
		{
			float lol = FCString::Atof(*string);

			if (lol < 50)
			{
				string = FString::FromInt(50);
				GameInstance->SetFov(50);
				CustomFov->SetText(FText::FromString(string));
				settings.FOV = 50;
				OnSettingChanged.Broadcast(settings);
			}
			else if (lol > 150)
			{
				string = FString::FromInt(150);
				GameInstance->SetFov(150);
				CustomFov->SetText(FText::FromString(string));
				settings.FOV = 150;
				OnSettingChanged.Broadcast(settings);
			}
			else
			{
				GameInstance->SetFov(lol);
				string = FString::SanitizeFloat(lol, 0);
				CustomFov->SetText(FText::FromString(string));
				settings.FOV = lol;
				OnSettingChanged.Broadcast(settings);
			}
		}
	}
	else
	{
		GameInstance->SetFov(90);
		string.Empty();
		string = FString::SanitizeFloat(90, 0);
		CustomFov->SetText(FText::FromString(string));
		settings.FOV = 90;
		OnSettingChanged.Broadcast(settings);
	}
}

void UOptions::TextConfirmHorizontalSensitivity(const FText& Text, ETextCommit::Type type)
{
	FString string = Text.ToString();

	if (string.IsEmpty())
	{
		if (GameInstance->bSensitivityVerticalSame)
		{
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
			VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
		}
		else
		{
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
		}
	}
	else
	{
		if (string.IsNumeric())
		{
			if (GameInstance->bSensitivityVerticalSame)
			{
				float lol = FCString::Atof(*string);

				if (lol <= GameInstance->Minimum)
				{
					GameInstance->SetHorizontalSensitivity(GameInstance->Minimum);
					GameInstance->SetVerticalSensitivity(GameInstance->Minimum);
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
					VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
					HorizontalSensitivitySlider->SetValue(0);
					VerticalSensitivitySlider->SetValue(0);
					settings.Sensitivity = GameInstance->Sensitivity;
					OnSettingChanged.Broadcast(settings);
					
				}
				else if (lol >= GameInstance->Maximum)
				{
					GameInstance->SetHorizontalSensitivity(GameInstance->Maximum);
					GameInstance->SetVerticalSensitivity(GameInstance->Maximum);
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
					VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
					HorizontalSensitivitySlider->SetValue(1);
					VerticalSensitivitySlider->SetValue(1);
					settings.Sensitivity = GameInstance->Sensitivity;
					OnSettingChanged.Broadcast(settings);
				}
				else
				{
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
					VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
					GameInstance->SetHorizontalSensitivity(lol);
					GameInstance->SetVerticalSensitivity(lol);
					HorizontalSensitivitySlider->SetValue(lol / (GameInstance->Maximum - GameInstance->Minimum));
					VerticalSensitivitySlider->SetValue(lol / (GameInstance->Maximum - GameInstance->Minimum));
					settings.Sensitivity = GameInstance->Sensitivity;
					OnSettingChanged.Broadcast(settings);
				}
			}
			else
			{
				float lol = FCString::Atof(*string);

				if (lol <= GameInstance->Minimum)
				{
					GameInstance->SetHorizontalSensitivity(GameInstance->Minimum);
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
					HorizontalSensitivitySlider->SetValue(0);
					settings.Sensitivity.X = GameInstance->Sensitivity.X;
					OnSettingChanged.Broadcast(settings);
				}
				else if (lol >= GameInstance->Maximum)
				{
					GameInstance->SetHorizontalSensitivity(GameInstance->Maximum);
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
					HorizontalSensitivitySlider->SetValue(1);
					settings.Sensitivity.X = GameInstance->Sensitivity.X;
					OnSettingChanged.Broadcast(settings);
				}
				else
				{
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
					GameInstance->SetHorizontalSensitivity(lol);
					HorizontalSensitivitySlider->SetValue(lol / (GameInstance->Maximum - GameInstance->Minimum));
					settings.Sensitivity.X = GameInstance->Sensitivity.X;
					OnSettingChanged.Broadcast(settings);
				}
			}
		}
		else
		{
			if (GameInstance->bSensitivityVerticalSame)
			{
				HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
				VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
			}
			else
			{
				HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
			}
		}
	}
}

void UOptions::TextConfirmVerticalSensitivity(const FText& Text, ETextCommit::Type type)
{
	FString string = Text.ToString();

	if (string.IsEmpty())
	{
		if (GameInstance->bSensitivityVerticalSame)
		{
			HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
			VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
		}
		else
		{
			VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
		}
	}
	else
	{
		if (string.IsNumeric())
		{
			if (GameInstance->bSensitivityVerticalSame)
			{
				float lol = FCString::Atof(*string);

				if (lol <= GameInstance->Minimum)
				{
					GameInstance->SetHorizontalSensitivity(GameInstance->Minimum);
					GameInstance->SetVerticalSensitivity(GameInstance->Minimum);
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
					VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
					HorizontalSensitivitySlider->SetValue(0);
					VerticalSensitivitySlider->SetValue(0);
					settings.Sensitivity.X = GameInstance->Sensitivity.X;
					settings.Sensitivity.Y = GameInstance->Sensitivity.Y;
					OnSettingChanged.Broadcast(settings);

				}
				else if (lol >= GameInstance->Maximum)
				{
					GameInstance->SetHorizontalSensitivity(GameInstance->Maximum);
					GameInstance->SetVerticalSensitivity(GameInstance->Maximum);
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
					VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
					HorizontalSensitivitySlider->SetValue(1);
					VerticalSensitivitySlider->SetValue(1);
					settings.Sensitivity.X = GameInstance->Sensitivity.X;
					settings.Sensitivity.Y = GameInstance->Sensitivity.Y;
					OnSettingChanged.Broadcast(settings);
				}
				else
				{
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
					VerticalSensitivityTextBox->SetText(FormatFloatToText(lol));
					GameInstance->SetHorizontalSensitivity(lol);
					GameInstance->SetVerticalSensitivity(lol);
					HorizontalSensitivitySlider->SetValue(lol / (GameInstance->Maximum - GameInstance->Minimum));
					VerticalSensitivitySlider->SetValue(lol / (GameInstance->Maximum - GameInstance->Minimum));
					settings.Sensitivity.X = GameInstance->Sensitivity.X;
					settings.Sensitivity.Y = GameInstance->Sensitivity.Y;
					OnSettingChanged.Broadcast(settings);
				}
			}
			else
			{
				float lol = FCString::Atof(*string);

				if (lol <= GameInstance->Minimum)
				{
					GameInstance->SetHorizontalSensitivity(GameInstance->Minimum);
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
					VerticalSensitivitySlider->SetValue(0);
					settings.Sensitivity.Y = GameInstance->Sensitivity.Y;
					OnSettingChanged.Broadcast(settings);
				}
				else if (lol >= GameInstance->Maximum)
				{
					GameInstance->SetHorizontalSensitivity(GameInstance->Maximum);
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
					VerticalSensitivitySlider->SetValue(1);
					settings.Sensitivity.Y = GameInstance->Sensitivity.Y;
					OnSettingChanged.Broadcast(settings);
				}
				else
				{
					HorizontalSensitivityTextBox->SetText(FormatFloatToText(lol));
					GameInstance->SetHorizontalSensitivity(lol);
					VerticalSensitivitySlider->SetValue(lol / (GameInstance->Maximum - GameInstance->Minimum));
					settings.Sensitivity.Y = GameInstance->Sensitivity.Y;
					OnSettingChanged.Broadcast(settings);
				}
			}
		}
		else
		{
			if (GameInstance->bSensitivityVerticalSame)
			{
				HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
				VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
			}
			else
			{
				VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
			}
		}
	}
}

void UOptions::TextConfirmCrosshairWidth(const FText& Text, ETextCommit::Type type)
{
	FString string = Text.ToString();

	if (string.IsEmpty())
	{
		CrosshairWidthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.X, 2, 200));
	}
	else
	{
		if (string.IsNumeric())
		{
			float lol = FCString::Atof(*string);

			if (lol < 0)
			{
				GameInstance->SetCrosshairDimensionsX(0);
				CrosshairWidthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.X, 2, 200));
				CrosshairWidthSlider->SetValue(0);
			}
			else if (lol > 200)
			{
				GameInstance->SetCrosshairDimensionsX(1);
				CrosshairWidthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.X, 2, 200));
				CrosshairWidthSlider->SetValue(1);
			}
			else
			{
				if (lol == 0)
				{
					GameInstance->SetCrosshairDimensionsX(0);
					CrosshairWidthSlider->SetValue(0);
				}
				else
				{
					CrosshairWidthTextBox->SetText(FormatFloatToText(lol, 0, 1));
					GameInstance->SetCrosshairDimensionsX(lol / 200);
					CrosshairWidthSlider->SetValue(lol / 200);
				}
			}
		}
		else
		{
			CrosshairWidthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.X, 2, 200));
		}
	}
}

void UOptions::TextConfirmCrosshairLength(const FText& Text, ETextCommit::Type type)
{
	FString string = Text.ToString();

	if (string.IsEmpty())
	{
		CrosshairLengthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.Y, 2, 200));
	}
	else
	{
		if (string.IsNumeric())
		{
			float lol = FCString::Atof(*string);

			if (lol < 0)
			{
				GameInstance->SetCrosshairDimensionsY(0);
				CrosshairLengthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.Y, 2, 200));
				CrosshairLengthSlider->SetValue(0);
			}
			else if (lol > 200)
			{
				GameInstance->SetCrosshairDimensionsY(1);
				CrosshairLengthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.Y, 2, 200));
				CrosshairLengthSlider->SetValue(1);
			}
			else
			{
				if (lol != 0)
				{
					GameInstance->SetCrosshairDimensionsY(lol / 200);
					CrosshairLengthSlider->SetValue(lol / 200);
				}
				else
				{
					GameInstance->SetCrosshairDimensionsY(0);
					CrosshairLengthSlider->SetValue(0);
					CrosshairLengthTextBox->SetText(FormatFloatToText(0, 0, 1));
				}
			}
		}
		else
		{
			CrosshairLengthTextBox->SetText(FormatFloatToText(GameInstance->CrosshairDimensions.Y, 2, 200));
		}
	}
}

void UOptions::TextConfirmCenterGap(const FText& Text, ETextCommit::Type type)
{
	FString string = Text.ToString();

	if (string.IsEmpty())
	{
		CenterGapTextBox->SetText(FormatFloatToText(GameInstance->CenterGap, 2, 100));
	}
	else
	{
		if (string.IsNumeric())
		{
			float lol = FCString::Atof(*string);

			if (lol < 0)
			{
				GameInstance->SetCenterGap(0);
				CenterGapTextBox->SetText(FormatFloatToText(GameInstance->CenterGap, 2, 100));
				CenterGapSlider->SetValue(0);
			}
			else if (lol > 100)
			{
				GameInstance->SetCenterGap(1);
				CenterGapTextBox->SetText(FormatFloatToText(GameInstance->CenterGap, 2, 100));
				CenterGapSlider->SetValue(1);
			}
			else
			{
				if (lol != 0)
				{
					GameInstance->SetCenterGap(lol / 100);
					CenterGapSlider->SetValue(lol / 100);
				}
				else
				{
					GameInstance->SetCenterGap(0);
					CenterGapTextBox->SetText(FormatFloatToText(0, 0, 1));
					CenterGapSlider->SetValue(0);
				}
			}
		}
		else
		{
			CenterGapTextBox->SetText(FormatFloatToText(GameInstance->CenterGap, 2, 100));
		}
	}
}

void UOptions::CustomFovSetting(FString string, ESelectInfo::Type type)
{
	if (string.Contains("Custom"))
	{
		FovTextBlock->SetVisibility(ESlateVisibility::Visible);
		CustomFov->SetVisibility(ESlateVisibility::Visible);
		GameInstance->SetFov(90);
		settings.FOV = GameInstance->FOVOfCharacter;
		OnSettingChanged.Broadcast(settings);
	}
	else if (string == TEXT("90°"))
	{
		FovTextBlock->SetVisibility(ESlateVisibility::Collapsed);
		CustomFov->SetVisibility(ESlateVisibility::Collapsed);
		GameInstance->SetFov(90);
		settings.FOV = GameInstance->FOVOfCharacter;
		OnSettingChanged.Broadcast(settings);
	}
	else if (string == TEXT("80°"))
	{
		FovTextBlock->SetVisibility(ESlateVisibility::Collapsed);
		CustomFov->SetVisibility(ESlateVisibility::Collapsed);
		GameInstance->SetFov(80);
		settings.FOV = GameInstance->FOVOfCharacter;
		OnSettingChanged.Broadcast(settings);
	}
}

inline FText UOptions::FormatFloatToText(float num, int32 numoffractionaldigits, float scale)
{
	float x = num * scale;
	
	FString string = FString::SanitizeFloat(x, 0);
	
	if (numoffractionaldigits != -1)
	{
		if (string.Contains("."))
		{
			string.RemoveAt(string.Find(".") + numoffractionaldigits + 1, string.Len() - (string.Find(".") + numoffractionaldigits + 1));
			return FText::FromString(string);
		}
	}

	return FText::FromString(string);
}

void UOptions::SensitivityTypeHelper(int32 mode, float maximum, float minimum, bool bSensitivityVerticalSame)
{
	float divideby = maximum - minimum;
	
	GameInstance->SetHorizontalSensitivity(ConvertSensitivity(GameInstance->Sensitivity.X,GameInstance->PreviousSensitivityModeDegree,GameInstance->SensitivityModeDegree,GameInstance->Maximum,GameInstance->Minimum));
	GameInstance->SetVerticalSensitivity(ConvertSensitivity(GameInstance->Sensitivity.Y, GameInstance->PreviousSensitivityModeDegree, GameInstance->SensitivityModeDegree, GameInstance->Maximum, GameInstance->Minimum));
	HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X));
	VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y));
	HorizontalSensitivitySlider->SetValue((GameInstance->Sensitivity.X - minimum) / divideby);
	VerticalSensitivitySlider->SetValue((GameInstance->Sensitivity.Y - minimum) / divideby);
}

float UOptions::ConvertSensitivity(float num, float currentdegree, float newdegree, float maximum, float minimum)
{
	float final4 = num * (currentdegree / newdegree);

	if (final4 >= maximum) { return maximum; }

	if (final4 <= minimum) { return minimum; }
	return final4;
}

void UOptions::InitializeSensitivityWidgetHelper(uint32 index, float maximum, float minimum)
{
	float lol = (GameInstance->Sensitivity.X / (maximum - minimum));
	float bob = (GameInstance->Sensitivity.Y / (maximum - minimum));

	if (lol >= 1)
	{
		lol = 1;
	}
	if (bob >= 1)
	{
		bob = 1;
	}

	SensitivityType->SetSelectedOption(SensitivityType->GetOptionAtIndex(index));
	HorizontalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.X, -1, 1));
	HorizontalSensitivitySlider->SetValue(lol);
	VerticalSensitivityTextBox->SetText(FormatFloatToText(GameInstance->Sensitivity.Y, -1, 1));
	VerticalSensitivitySlider->SetValue(bob);
}

