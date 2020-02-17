// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void AMyPlayerController::BeginPlay()
{
	GameInstance = Cast<UTheGameInstance>(GetGameInstance());
	
	SetMode(GameInstance->SensitivityMode);
	FOV(GameInstance->FOVOfCharacter);

	AddYawInput(GetWorld()->GetDeltaSeconds());
	AddPitchInput(GetWorld()->GetDeltaSeconds());
}

void AMyPlayerController::SetMode(float Mode)
{	
	if (Mode == CSGO)
	{
		InputYawScale = GameInstance->Sensitivity.X;
		InputPitchScale = -GameInstance->Sensitivity.Y;
		PlayerInput->SetMouseSensitivity(CSGO_Degree);
	}
	else if (Mode == Overwatch)
	{
		InputYawScale = GameInstance->Sensitivity.X;
		InputPitchScale = -GameInstance->Sensitivity.Y;
		PlayerInput->SetMouseSensitivity(Overwatch_Degree);
	}
	else if (Mode == FortniteConfig)
	{
		InputYawScale = GameInstance->Sensitivity.X;
		InputPitchScale = -GameInstance->Sensitivity.Y;
		PlayerInput->SetMouseSensitivity(FortniteConfig_Degree);
	}
	else if (Mode == FortniteSlider)
	{
		InputYawScale = GameInstance->Sensitivity.X;
		InputPitchScale = -GameInstance->Sensitivity.Y;
		PlayerInput->SetMouseSensitivity(FortniteSlider_Degree);
	}
	else if (Mode == Rainbow6)
	{
		InputYawScale = GameInstance->Sensitivity.X;
		InputPitchScale = -GameInstance->Sensitivity.Y;
		PlayerInput->SetMouseSensitivity(Rainbow6_Degree);
	}
	else
	{
		InputYawScale = GameInstance->Sensitivity.X;
		InputPitchScale =  -GameInstance->Sensitivity.Y;
		PlayerInput->SetMouseSensitivity(CSGO_Degree);
	}
}
