// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseTrackingController.generated.h"

DECLARE_EVENT(ABaseTrackingController,FWalkingStopped)
/**
 * 
 */
UCLASS()
class LEARNING_API ABaseTrackingController : public AAIController
{
	GENERATED_BODY()

public:
	FWalkingStopped OnWalkingStopped;
	FAIMoveRequest Request;

public:
	UFUNCTION()
	void MoveAround();
	void UpdateLocation();
	FVector GetRandomLocationWithRadius(float Radius);
	ABaseTrackingController();
	void Possess(APawn* InPawn) override;
	void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	void Tick(float DeltaSeconds) override;
};
