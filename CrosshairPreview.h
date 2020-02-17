// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "Image.h"
#include "TheGameInstance.h"
#include "CrosshairPreview.generated.h"
/**
 * 
 */
UCLASS()
class LEARNING_API UCrosshairPreview : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void CreateCrosshair();
	UFUNCTION(BlueprintCallable)
		void GetProperties();
	UFUNCTION()
		virtual bool Initialize() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	UPROPERTY()
		FLinearColor Color;
	UPROPERTY()
		FVector2D Dimensions;
	UPROPERTY()
		float CenterGap;
	UPROPERTY()
		bool bDot;
	UPROPERTY()
		UTheGameInstance* GameInstance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		UImage* Image1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		UImage* Image2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		UImage* Image3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		UImage* Image4;
	
};
