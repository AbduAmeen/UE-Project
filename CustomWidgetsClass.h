// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "Slider.h"
#include "TextBlock.h"
#include "TheGameInstance.h"
#include "CustomWidgetsClass.generated.h"
/**
 * 
 */
UCLASS()
class LEARNING_API UCustomWidgetsClass : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* RedSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* BlueSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* GreenSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USlider* AlphaSlider;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* RedValue;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* BlueValue;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* GreenValue;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* AlphaValue;
	UPROPERTY()
		UTheGameInstance* GameInstance;
public:
	UFUNCTION(BlueprintCallable)
		int32 ChangeToInt(float number);
	UFUNCTION(BlueprintCallable)
		void PrintValue(UTextBlock* block, int32 value);
	UFUNCTION(BlueprintCallable)
		void PrintValueAlpha(UTextBlock* block, float number);
	UFUNCTION()
		virtual bool Initialize() override;
	UFUNCTION()
		void ValueChangedRedSlider(float value);
	UFUNCTION()
		void ValueChangedBlueSlider(float value);
	UFUNCTION()
		void ValueChangedGreenSlider(float value);
	UFUNCTION()
		void ValueChangedAlphaSlider(float value);
};
