// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyCharacter.h"
#include "Target.h"
#include "MyGameMode.generated.h"



/**
 * 
 */
UCLASS()
class LEARNING_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
	
	void StartPlay() override;
	
	UFUNCTION(BlueprintPure)
		float GetAccuracy();

	UFUNCTION(BlueprintPure)
		FString GetCurrentMap();
	
	UFUNCTION()
		FHitResult FireResult(AMyCharacter* Character);

	UFUNCTION()
		void HandleResult(FHitResult FireResult);

	UFUNCTION()
		void ChangeMap(FString MapName);
	UFUNCTION()
		UPauseMenu* CreateMenu();
	UFUNCTION()
		void DestroyMenu(UPauseMenu* menu);
	
	

	/*Return Parmams:
0: There was no FireResult
1: FireResult is a target
2: FireResult isn't a target*/
	UFUNCTION()
	int32 Result(FHitResult FireResult);
	/*Cannot set ScaleOfTarget to less than 1. Don't change the Z value of the Scale.
	 *Set TimeAlive to 0 to keep the target*/
	UFUNCTION()
	ATarget* CreateTarget(FName Name, float TimeAlive, FVector ScaleOfTarget = FVector(1.0f, 1.0f, 1.0f));
	
	UPROPERTY(EditDefaultsOnly, Category = "Target")
		TSubclassOf<ATarget> TargetClass;
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
		TSubclassOf<UUserWidget> InformationClass;
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
		TSubclassOf<UUserWidget> CrosshairClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UOptions> OptionsClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UPauseMenu> PauseMenuClass;
	
	UPROPERTY()
		UUserWidget* AccuracyPtr;
	UPROPERTY()
		UTheGameInstance* GameInstance;
	UPROPERTY()
		UUserWidget* CrosshairPtr;
	UPROPERTY()
		UPauseMenu* PauseMenuPtr;
	UPROPERTY()
		UOptions* OptionsPtr;
	UPROPERTY()
		AMyCharacter* user;
	UPROPERTY()
		FTimerHandle TimerHWD;
	UPROPERTY()
		float TimeOfRound;
	UPROPERTY()
		float Accuracy;
	UPROPERTY()
		float TotalShotsMissed;
	UPROPERTY()
		float TotalShotsHit;
	UPROPERTY()
		FHitResult ResultOfFire;
	UPROPERTY()
		FString CurrentMap;
};
