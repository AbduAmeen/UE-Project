// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TheGameInstance.generated.h"

#define CSGO_Degree 0.022f
#define FortniteSlider_Degree 0.5555f
#define Overwatch_Degree 0.0066f
#define FortniteConfig_Degree 2.222f
#define Rainbow6_Degree 0.0057296f

#define CSGO 0
#define Overwatch 1
#define FortniteSlider 2
#define FortniteConfig 3
#define Rainbow6 4
#define Apex 5

/**
 * 
 */
UCLASS(config = YourGameSettings)
class LEARNING_API UTheGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	UPROPERTY(Config)
		FLinearColor ColorOfCrosshair;
	UPROPERTY(Config)
		bool bDot;
	UPROPERTY(Config)
		FVector2D CrosshairDimensions;
	UPROPERTY(Config)
		float CenterGap;
	UPROPERTY(Config)
		float FOVOfCharacter;
	UPROPERTY(Config)
		FVector2D Sensitivity;
	UPROPERTY(Config)
		bool bThirdPersonEnabled;
	UPROPERTY(Config)
		bool bFirstPersonEnabled;
	UPROPERTY(Config)
		int32 SensitivityMode;
	UPROPERTY()
		float SensitivityModeDegree;
	UPROPERTY(Config)
		bool bSensitivityVerticalSame;
	UPROPERTY(Config)
		bool bHidePlayerModel;
	UPROPERTY()
		float PreviousSensitivityModeDegree;
	UPROPERTY()
		float Minimum;
	UPROPERTY()
		float Maximum;
public:
	UFUNCTION(BlueprintCallable)
		void SetCrosshairColorRed(float Red);
	UFUNCTION(BlueprintCallable)
		void SetCrosshairColorBlue(float Blue);
	UFUNCTION(BlueprintCallable)
		void SetCrosshairColorGreen(float Green);
	UFUNCTION(BlueprintCallable)
		void SetCrosshairColorAlpha(float Alpha);
	UFUNCTION(BlueprintCallable)
		void SetCrosshairDimensionsX(float X);
	UFUNCTION(BlueprintCallable)
		void SetCrosshairDimensionsY(float Y);
	UFUNCTION(BlueprintCallable)
		void SetDot(bool enabled);
	UFUNCTION(BlueprintCallable)
		void SetCenterGap(float gap);
	UFUNCTION(BlueprintCallable)
		void SetFov(float fov);
	UFUNCTION(BlueprintCallable)
		void SetFirstPerson();
	UFUNCTION(BlueprintCallable)
		void SetThirdPerson();
	UFUNCTION(BlueprintCallable)
		void SetSensitivityMode(int32 mode);
	UFUNCTION(BlueprintCallable)
		void SetSensitivityModeDegree(int32 mode);
	UFUNCTION(BlueprintCallable)
		void SetPreviousSensitivityModeDegree(int32 mode);
	UFUNCTION(BlueprintCallable)
		void IsVertialSensitivityDifferent(bool set);
	UFUNCTION(BlueprintCallable)
		void SetHorizontalSensitivity(float lol);
	UFUNCTION(BlueprintCallable)
		void SetVerticalSensitivity(float lol);
	UFUNCTION(BlueprintCallable)
		void SetMaximum(int32 lol);
	UFUNCTION(BlueprintCallable)
		void SetMinimum(int32 mode);
	UFUNCTION(BlueprintCallable)
		void SetbSensitivityVerticalSame(bool lol);
	UFUNCTION(BlueprintCallable)
		void SaveTheSettings();
public:
	void CreateDefaultsIni();
	void ReadDefaults();
	UFUNCTION(BlueprintCallable)
		virtual void Init() override;
	bool CheckIfIni(const FString filepath);
};
