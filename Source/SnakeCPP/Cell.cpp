// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cell Mesh"));
	SetRootComponent(CellMesh);
	CellMesh->CastShadow = false;
	CellMesh->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

