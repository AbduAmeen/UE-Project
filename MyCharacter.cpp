// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Components/InputComponent.h"
#include "UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameMode.h"
#include "MyHUD.h"
#include "TrackingGamemode.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Create a first person camera component.
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 150;
	CameraSpringArm->SetRelativeLocation(FVector(-70.61116f, 17.699324f, 82.307327f));
	CameraSpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	CameraSpringArm->bDoCollisionTest = true;
	
	
	TheCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TheCamera"));
	TheCamera->SetupAttachment(RootComponent);
	TheCamera->bUsePawnControlRotation = true;

	ThirdPerson = 2;
	FirstPerson = 1;
	SwitchCamera(TheCamera, CameraSpringArm, ThirdPerson);
	bPressedCameraSwap = false;
	bFire = false;
	bPause = false;
	PrimaryActorTick.bCanEverTick = false;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		check(TheCamera != nullptr);
		GameInstance = Cast<UTheGameInstance>(GetWorld()->GetGameInstance());
	}	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveSide", this, &AMyCharacter::MoveSide).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("TurnUp", this, &AMyCharacter::AddControllerYawInput).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("TurnSide", this, &AMyCharacter::AddControllerPitchInput).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("CameraSwap", IE_Pressed, this, &AMyCharacter::CameraSwap).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("CameraSwap", IE_Released, this, &AMyCharacter::CameraSwapStop).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::FireStop).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("EscapeKey", IE_Pressed, this, &AMyCharacter::Pause).bExecuteWhenPaused = true;
}

void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyCharacter::MoveSide(float Value)
{
	if (Value != 0.0f)
	{	
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyCharacter::CameraSwap()
{
	bPressedCameraSwap = true;

	if (!GameInstance->bThirdPersonEnabled)
	{
		SwitchCamera(TheCamera, CameraSpringArm, ThirdPerson);
		GameInstance->SetThirdPerson();
	}
	else
	{
		SwitchCamera(TheCamera, CameraSpringArm, FirstPerson);
		GameInstance->SetFirstPerson();
	}
}

void AMyCharacter::CameraSwapStop()
{
	bPressedCameraSwap = false;
}


void AMyCharacter::Fire()
{
	bFire = true;
	float Distance = 8000.0f;
	FVector StartTrace = TheCamera->GetComponentLocation();
	FVector ForwardVector = TheCamera->GetForwardVector();
	FVector EndTrace = ((ForwardVector * Distance) + StartTrace);
	FCollisionQueryParams TraceParams;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams);
	
	ShotsFired += 1.0f;
	bFireHandled = false;
}

void AMyCharacter::FireStop()
{
	bFire = false;
}

void AMyCharacter::Pause()
{	
	bPause = true;
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FString string = UGameplayStatics::GetCurrentLevelName(GetWorld());

	if (string == "Tutorial_Map")
	{
		AMyGameMode* Gamemode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
		widget = Gamemode->CreateMenu();
		Controller->SetPause(bPause);
		MenuControls(true);
		Controller->SetInputMode(FInputModeGameAndUI());
		Controller->bShowMouseCursor = true;
	}
	else
	{
		ATrackingGamemode* Gamemode = Cast<ATrackingGamemode>(GetWorld()->GetAuthGameMode());
		widget = Gamemode->CreateMenu();
		Controller->SetPause(bPause);
		MenuControls(true);
		Controller->SetInputMode(FInputModeGameAndUI());
		Controller->bShowMouseCursor = true;
	}
}

void AMyCharacter::UnPause()
{
	if (!widget->Back())
	{
		FString string = UGameplayStatics::GetCurrentLevelName(GetWorld());
		if (string == "Tutorial_Map")
		{
			AMyGameMode* Gamemode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
			Gamemode->DestroyMenu(widget);
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			Controller->SetInputMode(FInputModeGameOnly());
			Controller->bShowMouseCursor = false;
			MenuControls(false);
			bPause = false;
			Controller->SetPause(bPause);
		}
		else
		{
			ATrackingGamemode* Gamemode = Cast<ATrackingGamemode>(GetWorld()->GetAuthGameMode());
			Gamemode->DestroyMenu(widget);
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			Controller->SetInputMode(FInputModeGameOnly());
			Controller->bShowMouseCursor = false;
			MenuControls(false);
			bPause = false;
			Controller->SetPause(bPause);
		}
	}	
}

void AMyCharacter::Enter()
{
	if (widget->QuitWidgetPtr != nullptr)
	{
		if (widget->QuitWidgetPtr->IsVisible())
		{
			widget->QuitWidgetPtr->Confirmed();
		}
	}
}

void AMyCharacter::MenuControls(bool offoron)
{
	if (offoron)
	{
		InputComponent->ClearActionBindings();
		InputComponent->AxisBindings.Empty();
		InputComponent->BindAction("EscapeKey", IE_Pressed, this, &AMyCharacter::UnPause).bExecuteWhenPaused = true;
		InputComponent->BindAction("Enter", IE_Pressed, this, &AMyCharacter::Enter).bExecuteWhenPaused = true;
		widget->SetKeyboardFocus();
	}
	else
	{
		InputComponent->ClearActionBindings();
		InputComponent->AxisBindings.Empty();
		SetupPlayerInputComponent(InputComponent);
	}
}


bool AMyCharacter::SwitchCamera(UCameraComponent* Camera, USpringArmComponent* SpringArm, int CameraType)
{
	if (CameraType == 1)
	{
		Camera->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, "head");
		Camera->SetRelativeLocation(FVector(4.0f, 0.0f, -6.0f));
		Camera->SetRelativeRotation(FRotator(-90.0f, 0.0f, 87.0f));
		return true;
	}

	if (CameraType == 2)
	{
		Camera->AttachToComponent(CameraSpringArm, FAttachmentTransformRules::KeepRelativeTransform,USpringArmComponent::SocketName);
		Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}

void AMyCharacter::HandleFire()
{
	bFireHandled = true;
}
