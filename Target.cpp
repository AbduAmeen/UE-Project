// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"
#include "Engine/Engine.h"
#include "ConstructorHelpers.h"



// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Material = CreateDefaultSubobject<UMaterial>(TEXT("Material"));
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetMaterial(0, Material);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}