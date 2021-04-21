// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeCPPGameModeBase.h"
#include "Board.h"
#include "SnakeHead.h"
#include "Kismet/GameplayStatics.h"

void ASnakeCPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnBoard();
	
	auto Snake = Cast<ASnakeHead>(UGameplayStatics::GetPlayerPawn(this , 0));
	Snake->Board = BoardRef;
}

void ASnakeCPPGameModeBase::SpawnBoard()
{
	BoardRef = GetWorld()->SpawnActor<ABoard>(BoardClass, FVector(0, 0, 0), FRotator(0, 0, 0));
}

