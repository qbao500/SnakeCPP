// Fill out your copyright notice in the Description page of Project Settings.


#include "AIHead.h"


#include "Board.h"
#include "Kismet/GameplayStatics.h"
#include "Fruit.h"

void AAIHead::BeginPlay()
{
	Super::BeginPlay();

	DisableInput(UGameplayStatics::GetPlayerController(this, 0));

	// Ignore fruit and self
	CollisionQueryParams.AddIgnoredActor(Cast<AActor>(Board->FruitRef));
	CollisionQueryParams.AddIgnoredActor(this);
}

void AAIHead::MainMovement()
{
	// Target to fruit
	DecideMovement();

	// But still check for danger
	CheckBorder();
	CheckAhead();

	// Now real move
	Super::MainMovement();
}

void AAIHead::DecideMovement()
{
	// It's time to decide (when snake in line with fruit)
	if (GetActorLocation().X == FruitLocation.X || GetActorLocation().Y == FruitLocation.Y)
	{
		bShouldDecide = true;
	}

	// Not always decide per tick
	if (!bShouldDecide) return;

	// Get normalize direction (this can be diagonal)
	FVector NewDirection = FruitLocation - GetActorLocation();
	if (NewDirection.Normalize())
	{
		// Make it vertical or horizontal
		float NewXabs = abs(NewDirection.X);
		float NewYabs = abs(NewDirection.Y);
		if (NewXabs != 1 && NewXabs >= NewYabs)
		{
			NewDirection = FVector(NewDirection.X / NewXabs, 0, 0);
		}
		else if (NewYabs != 1 && NewXabs < NewYabs)
		{
			NewDirection = FVector(0, NewDirection.Y / NewYabs, 0);
		}
	}
	else
	{
		// Sometimes NewDirection cant be normalized because it's not "safe" to do that
		// If it's not safe, it return Vector Zero, which make the snake stop
		return;
	}

	// Prevent AI going reverse direction
	if (NewDirection * -1 == MoveDirection)
	{
		UE_LOG(LogTemp,Warning,TEXT("No turn-around plz"));
		return;
	}

	// If new direction has tail
	if (LineTrace(GetActorLocation(), NewDirection))
	{
		// Abort mission
		return;
	}

	// If pass all, set move direction to new direction
	MoveDirection = NewDirection;
	bShouldDecide = false; // Comment this line if you want the snake go brrrrr
}

void AAIHead::CheckBorder()
{
	// Check if reach border of the board
	FVector CurrentLocation = GetActorLocation();

	// If yes, Shoot a ray to the opposite location, before going cross border
	// Bottom border
	if (CurrentLocation.X == (Board->BoardRow - 1) * -100 && IsMovingDown())
	{
		if (LineTrace(FVector(100, CurrentLocation.Y, 0)))
		{
			CheckTwoSides(FVector(MoveDirection.Y, MoveDirection.X, 0));
		}
	}
	// Upper border
	else if (CurrentLocation.X == 0 && IsMovingUp())
	{
		if (LineTrace(FVector(Board->BoardRow * -100, CurrentLocation.Y, 0)))
		{
			CheckTwoSides(FVector(MoveDirection.Y, MoveDirection.X, 0));
		}
	}
	// Right border
	else if (CurrentLocation.Y == (Board->BoardColumn - 1) * 100 && IsMovingRight())
	{
		if (LineTrace(FVector(CurrentLocation.X, -100, 0)))
		{
			CheckTwoSides(FVector(MoveDirection.Y, MoveDirection.X, 0));
		}
	}
	// Left border
	else if (CurrentLocation.Y == 0 && IsMovingLeft())
	{
		if (LineTrace(FVector(CurrentLocation.X, Board->BoardColumn * 100, 0)))
		{
			CheckTwoSides(FVector(MoveDirection.Y, MoveDirection.X, 0));
		}
	}
}
	
void AAIHead::CheckAhead()
{
	// Front line
	if (LineTrace(GetActorLocation()))
	{		
		UE_LOG(LogTemp, Warning, TEXT("Almost Hit %s"), *Hit.Actor->GetName());

		// If danger ahead, check left and right
		CheckTwoSides(FVector(MoveDirection.Y, MoveDirection.X, 0));
	}
}

void AAIHead::CheckTwoSides(FVector NewDirection)
{
	// 700 is around half of the board, need to check that far to see which side is safer
	// One side first
	if (!LineTrace(GetActorLocation(), NewDirection, 700))
	{
		// If this way is safe, move to its direction
		MoveDirection = NewDirection;
		return;
	}
		
	// Other side
	if (!LineTrace(GetActorLocation(), NewDirection, -700))
	{
		// If this way is safe, move to its direction
		MoveDirection = NewDirection;
		return;
	}

	// If both are not that safe, just take a risk
	MoveDirection = NewDirection;
}

bool AAIHead::LineTrace(FVector Start, FVector Direction, float Length)
{
	// If no direction set, make it current move direction
	if (Direction == FVector(0, 0, 0))
	{
		Direction = MoveDirection;
	}
	
	FVector End = Start + (Direction * Length);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CollisionQueryParams))
	{
		return true;
	}

	return false;
}
