// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheGameInstance.h"
#include "MyPlayerController.generated.h"

#define CSGO_Degree 0.022f
#define FortniteSlider_Degree 0.5555f
#define Overwatch_Degree 0.0066f
#define FortniteConfig_Degree 2.222f
#define Rainbow6_Degree 0.0057296f
/**
 * 
 */
UCLASS()
class LEARNING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	//Use one of the macros
	UFUNCTION()
		void SetMode(float Mode);
public:
	UPROPERTY()
		UTheGameInstance* GameInstance;
	UPROPERTY()
		FVector2D Sensitivity;

};
