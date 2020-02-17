// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "AIPawnMovement.h"
#include "BaseTrackingTarget.generated.h"

UCLASS()
class LEARNING_API ABaseTrackingTarget : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY()
		bool bShouldFireBack;
	UPROPERTY()
		int32 Health;
	UPROPERTY()
		int32 MagazineCount;
	UPROPERTY()
		int32 AmmoTotal;
	UPROPERTY()
		float Speed;

public:
	// Sets default values for this pawn's properties
	ABaseTrackingTarget();

	// Called to bind functionality to input
	void SetHealth(int32 health);
	void SetFireBack(bool lol);
	void SetMagCount(int32 count);
	void SetAmmoTotal(int32 total);
	void SetSpeed(float speed);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
