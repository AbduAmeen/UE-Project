// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "TheGameInstance.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void DrawHUD() override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FLinearColor ColorOfCrosshair;
	UPROPERTY()
		FVector2D CenterOfScreen;
	UPROPERTY()
		UTheGameInstance* GameInstance;
public:
	UFUNCTION(BlueprintCallable)
		void SetColor(FLinearColor color);
};