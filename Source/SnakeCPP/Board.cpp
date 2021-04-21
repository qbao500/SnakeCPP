// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Cell.h"
#include "Fruit.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	GenerateBoard();
	SpawnFruit();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::GenerateBoard()
{
	FVector Location = GetActorLocation();
	const float StartRow = Location.Y;
	
	for (int32 Row = 0; Row < BoardRow; Row++)
	{
		for (int32 Column = 0; Column < BoardColumn; Column++)
		{
			// First tile is at board original location			
			GetWorld()->SpawnActor<ACell>(CellClass, Location, FRotator(0, 0, 0));

			// Go right
			Location.Y += 100;

			// Reset when reach max
			if (Column >= (BoardColumn - 1)) Location.Y = StartRow;
		}

		// Go down
		Location.X -= 100;
	}
}

void ABoard::SpawnFruit()
{
	FruitRef = GetWorld()->SpawnActor<AFruit>(FruitClass);
	FruitRef->BoardRef = this;
	FruitRef->ChangeLocation();
}

