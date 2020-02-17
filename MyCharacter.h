// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "TheGameInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "PauseMenu.h"
#include "MyCharacter.generated.h"



UCLASS()
class LEARNING_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;
public:	
	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UCameraComponent* TheCamera;
	UPROPERTY()
		bool bPressedCameraSwap;
	UPROPERTY()
		bool bFire;
	UPROPERTY()
		bool bPause;
	UPROPERTY()
		UTheGameInstance* GameInstance;
public:
	UFUNCTION()
		void MoveForward(float Val);
	//handles strafing
	UFUNCTION()
		void MoveSide(float Val);
	//Handles swaping camera on press
	UFUNCTION()
		void CameraSwap();
	//Clears swaping camera Flag
	UFUNCTION()
		void CameraSwapStop();
	UFUNCTION()
		void Fire();
	UFUNCTION()
		void FireStop();
	UFUNCTION()
		void Pause();
	UFUNCTION()
		void UnPause();
	UFUNCTION()
		void Enter();

	void MenuControls(bool offoron);
	UPauseMenu* widget;
public:
	//If False there is an error. If true it was successful
	bool SwitchCamera(UCameraComponent* Camera, USpringArmComponent* SpringArm, int CameraType);
	//Set Spring Arm properties when changing views
	void HandleFire();
	UCameraComponent* GetTheCamera() const { return TheCamera; }
	
	//A camera type used for SwitchCamera
	int32 ThirdPerson;
	//A camera type used for SwitchCamera
	int32 FirstPerson;
	float ShotsFired;
	FHitResult HitResult;
	bool bFireHandled;
	
};
