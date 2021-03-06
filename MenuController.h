// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API AMenuController : public APlayerController
{
	GENERATED_BODY()

	void BeginPlay() override;

	virtual void SetupInputComponent() override;
	void Back();
	void Enter();
};
