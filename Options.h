// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "Slider.h"
#include "ComboBoxString.h"
#include "EditableTextBox.h"
#include "Button.h"
#include "TextBlock.h"
#include "WidgetSwitcher.h"
#include "ScrollBox.h"
#include "CustomWidgetsClass.h"
#include "MyPlayerController.h"
#include "CrosshairPreview.h"
#include "TheGameInstance.h"
#include "CheckBox.h"
#include "Delegates/Delegate.h"
#include "Options.generated.h"

#define CSGO 0
#define Overwatch 1
#define FortniteSlider 2
#define FortniteConfig 3
#define Rainbow6 4
#define Apex 5

USTRUCT()
struct FUpdatedPlayerSettings
{
	GENERATED_BODY()

	UPROPERTY()
	FLinearColor Color;
	UPROPERTY()
	bool Dot;
	UPROPERTY()
	FVector2D Dimensions;
	UPROPERTY()
	FVector2D Sensitivity;
	UPROPERTY()
	float Gap;
	UPROPERTY()
	float FOV;
	UPROPERTY()
	bool bThirdPerson;
	UPROPERTY()
	bool bFirstPerson;
	UPROPERTY()
	int32 SensitivityMode;
	UPROPERTY()
	bool bVerticalSame;
	UPROPERTY()
	bool hideplayer;
};

DECLARE_EVENT_OneParam(UOptions, FSettingChanged, FUpdatedPlayerSettings)
/**
 * 
 */


UCLASS()
class LEARNING_API UOptions : public UUserWidget
{
	GENERATED_BODY()
public:

		FSettingChanged OnSettingChanged;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* HorizontalSensitivitySlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* VerticalSensitivitySlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* CenterGapSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* CrosshairWidthSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* CrosshairLengthSlider;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UComboBoxString* SensitivityType;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UComboBoxString* FovComboBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UComboBoxString* CrosshairType;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* HorizontalSensitivityTextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* VerticalSensitivityTextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* CenterGapTextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* CrosshairLengthTextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* CrosshairWidthTextBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* CustomFov;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* GameSettings;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* SaveSettingsButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* CancelButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* CrosshairSettings;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* ResetToDefaultButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* GameSettingsScrollBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* CrosshairScrollBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* FovTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UWidgetSwitcher* TheWidgetSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UCustomWidgetsClass* CrosshairColors;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UCrosshairPreview* CrosshairPreview;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UCheckBox* VerticalMatchHorizontal;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UCheckBox* HidePlayerModelCheckbox;

	UPROPERTY()
		UTheGameInstance* GameInstance;
	UPROPERTY()
		UUserWidget* MenuPtr;
	UPROPERTY()
		FUpdatedPlayerSettings settings;
public:
	UFUNCTION()
		void Cancel();
	UFUNCTION()
		void OpenCrosshairSettings();
	UFUNCTION()
		void OpenGameSettings();
	UFUNCTION()
		void ValueChangedCrosshairWidth(float value);
	UFUNCTION()
		void ValueChangedCrosshairLength(float value);
	UFUNCTION()
		void ValueChangedCenterGap(float value);
	
	UFUNCTION()
		void TextChangeCrosshairLength(const FText& Text);
	UFUNCTION()
		void TextConfirmCrosshairLength(const FText& Text, ETextCommit::Type type);
	UFUNCTION()
		void TextChangeCrosshairWidth(const FText& Text);
	UFUNCTION()
		void TextConfirmCrosshairWidth(const FText& Text, ETextCommit::Type type);
	UFUNCTION()
		void TextChangeCenterGap(const FText& Text);
	UFUNCTION()
		void TextConfirmCenterGap(const FText& Text, ETextCommit::Type type);
	UFUNCTION()
		void CustomFovSetting(FString string, ESelectInfo::Type type);
	UFUNCTION()
		void InitializeWidgets();
	UFUNCTION()
		void TextChangeCustomFov(const FText& Text);
	UFUNCTION()
		void TextChangeVerticalTextBox(const FText& Text);
	UFUNCTION()
		void TextChangeHorizontalTextBox(const FText& Text);
	UFUNCTION()
		void TextConfirmCustomFov(const FText& Text, ETextCommit::Type type);
	UFUNCTION()
		void TextConfirmHorizontalSensitivity(const FText& Text, ETextCommit::Type type);
	UFUNCTION()
		void TextConfirmVerticalSensitivity(const FText& Text, ETextCommit::Type type);
	UFUNCTION()
	//Add to this for new sensitivities
		void SelectionChangeSensitivityType(FString string, ESelectInfo::Type type);
	UFUNCTION()
		void ValueChangedHorizontalSensitivitySlider(float value);
	UFUNCTION()
		void ValueChangedVerticalSensitivitySlider(float value);
	UFUNCTION()
		void CheckboxVerticalMatchHorizontal(bool lol);
	UFUNCTION()
		void SaveSettingsDele();
	UFUNCTION()
		void ResetToDefault();
	UFUNCTION()
		void HidePlayerModel(bool lol);
	

	UFUNCTION()
		virtual bool Initialize() override;
	FString tempstring;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	//float num: float you want to convert
	//uint32 numoffractionaldigits: number of factional digits that you want, -1 for no limiting
	//float scale: scale of num that you want to set it to, 1 is to not scale, 
	static inline FText FormatFloatToText(float num, int32 numoffractionaldigits = -1, float scale = 1);
	void SensitivityTypeHelper(int32 mode, float maximum, float minimum, bool bSensitivityVerticalSame);
	static float ConvertSensitivity(float num, float currentdegree, float newdegree, float maximum, float minimum);
	void InitializeSensitivityWidgetHelper(uint32 index, float maximum, float minimum);
	void TextChange(UEditableTextBox* ptr, const FText& Text);
	void CheckIfWithin(float& value,float maximum,float minimum);
	void InitializeSettings();
};
