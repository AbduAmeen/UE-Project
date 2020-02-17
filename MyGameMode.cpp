// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UserWidget.h"
#include "MyHUD.h"


void AMyGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (user != nullptr)
	{
		GetAccuracy();
		if (!user->bFireHandled)
		{
		HandleResult(FireResult(user));
		
		if (Result(user->HitResult) == 1)
		{
			user->HitResult.GetActor()->Destroy();
			CreateTarget(TEXT("Target"), 0.0f);
		}
		user->HandleFire();
		}
	}
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();
	TimeOfRound = 10.0f;
	TotalShotsMissed = 0.0f;
	TotalShotsHit = 0.0f;
	Accuracy = 0.0f;
	ResultOfFire.Reset();

	user = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
	AMyPlayerController* Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameInstance = Cast<UTheGameInstance>(GetGameInstance());
	
	Controller->SetInputMode(FInputModeGameOnly());

	PauseMenuPtr = Cast<UPauseMenu>(CreateWidget(Controller, PauseMenuClass));
	OptionsPtr = Cast<UOptions>(CreateWidget(Controller, OptionsClass));
	
	if (user != nullptr)
	{
		if (InformationClass != nullptr)
		{
			AccuracyPtr = CreateWidget<UUserWidget>(GetWorld(), InformationClass);
			AccuracyPtr->AddToViewport();
		}

		if (CrosshairClass != nullptr)
		{
			CrosshairPtr = CreateWidget<UUserWidget>(GetWorld(), CrosshairClass);
			CrosshairPtr->AddToViewport();
		}

		if (PauseMenuPtr != nullptr)
		{
			PauseMenuPtr->AddToViewport();
			PauseMenuPtr->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (OptionsPtr != nullptr)
		{
			OptionsPtr->AddToViewport();
			OptionsPtr->SetVisibility(ESlateVisibility::Collapsed);
			OptionsPtr->MenuPtr = PauseMenuPtr;
			PauseMenuPtr->OptionsPtr = OptionsPtr;
		}
	}
	ATarget* Target1 = CreateTarget(TEXT("Target"), 0.0f);
	StartMatch();	
}

float AMyGameMode::GetAccuracy()
{
	if (user->ShotsFired == 0)
	{
		Accuracy = 0.0f;
	}
	else
	{
		Accuracy = TotalShotsHit / user->ShotsFired;
		Accuracy *= 100;
	}
	return Accuracy;
}

FString AMyGameMode::GetCurrentMap()
{
	return GetWorld()->GetMapName();
}

FHitResult AMyGameMode::FireResult(AMyCharacter* Character)
{
	if (Character->HitResult.Actor != nullptr)
	{
		ResultOfFire = Character->HitResult;
		return ResultOfFire;
	}
	
	return ResultOfFire;
}

void AMyGameMode::HandleResult(FHitResult FireResult)
{
	if (Result(FireResult) == 1)
	{
		TotalShotsHit++;
	}
	else if (Result(FireResult) == 2)
	{
		TotalShotsMissed++;
	}
}

void AMyGameMode::ChangeMap(FString MapName)
{
	if (GetCurrentMap() != MapName)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
	}
}

UPauseMenu* AMyGameMode::CreateMenu()
{
	PauseMenuPtr->SetVisibility(ESlateVisibility::Visible);
	return PauseMenuPtr;
}

void AMyGameMode::DestroyMenu(UPauseMenu* menu)
{
	menu->SetVisibility(ESlateVisibility::Collapsed);
	menu = nullptr;
}

int32 AMyGameMode::Result(FHitResult FireResult)
{
	if (FireResult.GetActor() != nullptr)
	{
		FString Rand = FireResult.Actor->GetName();
		
		if (Rand.Contains("Target")) { return 1; }
		return 2;
	}
	return 0;
}

ATarget* AMyGameMode::CreateTarget(FName Name, float TimeAlive, FVector ScaleOfTarget)
{
	if (ScaleOfTarget.Z != 1.0f)
	ScaleOfTarget.Z = 1.0f;

	ATarget* Whoop = nullptr;
	FActorSpawnParameters SpawnParam;
	SpawnParam.Name = Name;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParam.Owner = this;
	
	const FRotator Rotation = FRotator(180.0f, 90.0f, 180.0f);
	const float XCor = 264.0f;

	float YCor = FMath::RandRange(-839.0f, 864.0f);
	float ZCor = FMath::RandRange(127.0f, 625.0f);

	//FVector Location = FVector(XCor, YCor, ZCor);
	FVector Location = FVector(XCor, YCor, ZCor);
	
	Whoop = GetWorld()->SpawnActor<ATarget>(TargetClass,Location, Rotation, SpawnParam);

	if (Whoop != nullptr)
	{
		Whoop->SetActorScale3D(ScaleOfTarget);
		Whoop->SetLifeSpan(TimeAlive);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Target Didn't Spawn"));
	}

	return Whoop;
}
