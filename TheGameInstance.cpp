// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGameInstance.h"
#include "Engine/Engine.h"
#include "ConfigCacheIni.h"

void UTheGameInstance::SetCrosshairColorRed(float Red)
{
	ColorOfCrosshair.R = Red;
}

void UTheGameInstance::SetCrosshairColorBlue(float Blue)
{
	ColorOfCrosshair.B = Blue;
}

void UTheGameInstance::SetCrosshairColorGreen(float Green)
{
	ColorOfCrosshair.G = Green;
}

void UTheGameInstance::SetCrosshairColorAlpha(float Alpha)
{
	ColorOfCrosshair.A = Alpha;
}

void UTheGameInstance::SetCrosshairDimensionsX(float X)
{
	CrosshairDimensions.X = X;
}

void UTheGameInstance::SetCrosshairDimensionsY(float Y)
{
	CrosshairDimensions.Y = Y;
}

void UTheGameInstance::SetDot(bool enabled)
{
	bDot = enabled;
}

void UTheGameInstance::SetCenterGap(float gap)
{
	CenterGap = gap;
}

void UTheGameInstance::SetFov(float fov)
{
	FOVOfCharacter = fov;
}

void UTheGameInstance::SetFirstPerson()
{
	bThirdPersonEnabled = false;
	bFirstPersonEnabled = true;
}

void UTheGameInstance::SetThirdPerson()
{
	bThirdPersonEnabled = true;
	bFirstPersonEnabled = false;
}

void UTheGameInstance::SetSensitivityMode(int32 mode)
{
	SetPreviousSensitivityModeDegree(SensitivityMode);
	SensitivityMode = mode;
	SetSensitivityModeDegree(SensitivityMode);
	SetMaximum(mode);
	SetMinimum(mode);
}

void UTheGameInstance::SetSensitivityModeDegree(int32 mode)
{
	if (mode == 0 || mode == 5)
	{
		SensitivityModeDegree = CSGO_Degree;
	}
	else if (mode == 1)
	{
		SensitivityModeDegree = Overwatch_Degree;
	}
	else if (mode == 2)
	{
		SensitivityModeDegree = FortniteSlider_Degree;
	}
	else if (mode == 3)
	{
		SensitivityModeDegree = FortniteConfig_Degree;
	}
	else if (mode == 4)
	{
		SensitivityModeDegree = Rainbow6_Degree;
	}
	else
	{
		SensitivityModeDegree = CSGO_Degree;
	}
}

void UTheGameInstance::SetPreviousSensitivityModeDegree(int32 mode)
{
	if (mode == 0 || mode == 5)
	{
		PreviousSensitivityModeDegree = CSGO_Degree;
	}
	else if (mode == 1)
	{
		PreviousSensitivityModeDegree = Overwatch_Degree;
	}
	else if (mode == 2)
	{
		PreviousSensitivityModeDegree = FortniteSlider_Degree;
	}
	else if (mode == 3)
	{
		PreviousSensitivityModeDegree = FortniteConfig_Degree;
	}
	else if (mode == 4)
	{
		PreviousSensitivityModeDegree = Rainbow6_Degree;
	}
	else
	{
		PreviousSensitivityModeDegree = CSGO_Degree;
	}
}

void UTheGameInstance::IsVertialSensitivityDifferent(bool set)
{
	bSensitivityVerticalSame = set;
}

void UTheGameInstance::SetHorizontalSensitivity(float lol)
{
	Sensitivity.X = lol;
}

void UTheGameInstance::SetVerticalSensitivity(float lol)
{
	Sensitivity.Y = lol;
}

void UTheGameInstance::SetMaximum(int32 mode)
{
	if (mode == 0)
	{
		Maximum = 8;
	}
	else if (mode == 1 || mode == 4)
	{
		Maximum = 100;
	}
	else if (mode == 2 || mode == 3)
	{
		Maximum = 1;
	}
	else if (mode == 5)
	{
		Maximum = 20;
	}
	else
	{
		Maximum = 1;
	}
}

void UTheGameInstance::SetMinimum(int32 mode)
{
	if (mode == 0)
	{
		Minimum = 0.05;
	}
	else if (mode == 1 || mode == 4)
	{
		Minimum = 1;
	}
	else if (mode == 2 || mode == 3 || mode == 5)
	{
		Minimum = 0.01;
	}
	else
	{
		Minimum = 0.01;
	}
}

void UTheGameInstance::SetbSensitivityVerticalSame(bool lol)
{
	bSensitivityVerticalSame = lol;
}

void UTheGameInstance::SaveTheSettings()
{
	FString string3 = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + TEXT("Saved/Config/Windows/YourGameSettings.ini"));
		
	SaveConfig(CPF_Config,*string3);
}

void UTheGameInstance::CreateDefaultsIni()
{
	FString cs = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + TEXT("Saved/Config/Windows/Default.ini"));
	FLinearColor basecolor(1, 1, 1, 1);
	bool dot = false;
	FVector2D duck(0.018109, 0.091302);
	float gap = 0.121694;
	float fov = 90.0f;
	FVector2D dup(1.400000, 1.400000);
	bool boi = true;
	bool girl = false;
	int32 mode = 0;
	bool dog = true;
	bool cat = false;
	
	ColorOfCrosshair = basecolor;
	bDot = dot;
	CrosshairDimensions = duck;
	CenterGap = gap;
	FOVOfCharacter = fov;
	Sensitivity = dup;
	bThirdPersonEnabled = boi;
	bFirstPersonEnabled = girl;
	SensitivityMode = mode;
	bSensitivityVerticalSame = dog;
	bHidePlayerModel = cat;

	SaveConfig(CPF_Config, *cs);
}

void UTheGameInstance::ReadDefaults()
{
	LoadConfig(StaticClass(), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + TEXT("Saved/Config/Windows/Default.ini")));
}

void UTheGameInstance::Init()
{
	FString defaults = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + TEXT("Saved/Config/Windows/Default.ini"));
	
	if (!CheckIfIni(defaults))
	{
		CreateDefaultsIni();
	}
	
	if (!CheckIfIni(FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + TEXT("Saved/Config/Windows/YourGameSettings.ini"))))
	{
		ReadDefaults();
		SaveTheSettings();
	}

	SetSensitivityMode(SensitivityMode);
}


bool UTheGameInstance::CheckIfIni(const FString filepath)
{
	if (GConfig->IsReadyForUse())
	{
		FPaths* file;
		if (file->FileExists(filepath)) { return true; }
	}
	return false;
}
