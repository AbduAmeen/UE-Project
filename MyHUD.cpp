// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "CanvasItem.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"



void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	GameInstance = Cast<UTheGameInstance>(GetGameInstance());
	AMyCharacter* Character = Cast <AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	CenterOfScreen.X = Canvas->ClipX * 0.5f;
	CenterOfScreen.Y = Canvas->ClipY * 0.5f;
}

void AMyHUD::SetColor(FLinearColor color)
{
	ColorOfCrosshair = color;
}
