// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTrackingController.h"
#include "BaseTrackingTarget.h"
#include "MyCharacter.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


ABaseTrackingController::ABaseTrackingController()
{
}

void ABaseTrackingController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	
	ABaseTrackingTarget* AICharacter = Cast<ABaseTrackingTarget>(InPawn);
	
	if (AICharacter != nullptr)
	{
		OnWalkingStopped.AddUFunction(this, "MoveAround");
	}
}

void ABaseTrackingController::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);
	
	if (GetPawn() != nullptr)
	{
		if (GetPawn()->GetVelocity().Size() <= 0) { OnWalkingStopped.Broadcast(); };
	}
}

void ABaseTrackingController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetPawn() != nullptr) {if (GetPawn()->GetVelocity().Size() <= 0) { OnWalkingStopped.Broadcast(); }}
}

void ABaseTrackingController::MoveAround()
{
	ABaseTrackingTarget* Pawn = Cast<ABaseTrackingTarget>(GetPawn());
	FTimerHandle TimerHandle;
	
	Request.SetGoalLocation(GetRandomLocationWithRadius(1000));
	Request.SetCanStrafe(true);
	
	MoveTo(Request);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ABaseTrackingController::UpdateLocation,0.5,true);
}

void ABaseTrackingController::UpdateLocation()
{
	Request.UpdateGoalLocation(GetRandomLocationWithRadius(1000));
}

FVector ABaseTrackingController::GetRandomLocationWithRadius(float Radius)
{
	UNavigationSystemV1* NavSys = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

	if (NavSys != nullptr)
	{
		FNavLocation RandomPt;

		const bool bFound = NavSys->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), Radius, RandomPt);

		if (bFound)
		{
			return RandomPt.Location;
		}
	}
	return GetPawn()->GetActorLocation();
}
