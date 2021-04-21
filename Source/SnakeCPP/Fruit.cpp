// Fill out your copyright notice in the Description page of Project Settings.


#include "Fruit.h"

#include "AIHead.h"
#include "Board.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeHead.h"
#include "SnakeTail.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AFruit::AFruit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FruitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fruit Mesh"));
	SetRootComponent(FruitMesh);
	FruitMesh->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	FruitMesh->SetCollisionProfileName("OverlapAll");
}

// Called when the game starts or when spawned
void AFruit::BeginPlay()
{
	Super::BeginPlay();

	FruitMesh->OnComponentBeginOverlap.AddDynamic(this, &AFruit::OnSnakeOverlapBegin);

	SnakeHead = Cast<ASnakeHead>(UGameplayStatics::GetPlayerPawn(this, 0));
	AIHead = Cast<AAIHead>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AFruit::ChangeLocation()
{
	if (!BoardRef) return;

	// Random new location
	int32 Row = FMath::RandRange(0, BoardRef->BoardRow - 1) * 100;
	int32 Column = FMath::RandRange(0, BoardRef->BoardColumn - 1) * -100;
	FVector NewLocation = FVector(Column, Row, 0);

	// Let AI know fruit location
	if (AIHead)
	{
		AIHead->FruitLocation = NewLocation;
	}

	// Move to that location
	SetActorLocation(NewLocation);
}

void AFruit::OnSnakeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// If spawn on tail
	if (Cast<ASnakeTail>(OtherActor))
	{
		ChangeLocation();
	}
	
	if (OtherActor == SnakeHead)
	{		
		SnakeHead->PlayerAteFruit();
		ChangeLocation();
	}
	
}



