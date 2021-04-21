// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"


#include "Board.h"
#include "SnakeTail.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = MoveRate;

	SnakeHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Snake Head"));
	SetRootComponent(SnakeHead);
	SnakeHead->SetCollisionProfileName("OverlapAll");
	SnakeHead->CastShadow = false;
}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();

	AddTail();
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MainMovement();
}

// Called to bind functionality to input
void ASnakeHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("MoveUp"), IE_Pressed, this, &ASnakeHead::MoveUp);
	PlayerInputComponent->BindAction(TEXT("MoveDown"), IE_Pressed, this, &ASnakeHead::MoveDown);
	PlayerInputComponent->BindAction(TEXT("MoveRight"), IE_Pressed, this, &ASnakeHead::MoveRight);
	PlayerInputComponent->BindAction(TEXT("MoveLeft"), IE_Pressed, this, &ASnakeHead::MoveLeft);
}

void ASnakeHead::MainMovement()
{
	// Save previous location for tails
	PreviousLocation = GetActorLocation();
	// Move to new one
	AddActorWorldOffset(MoveDirection * StepSize);

	// Check if out of board
	CrossBorder();
	
	// If no tail yet, return
	if (FirstTail == nullptr) return;

	// Move tails
	FirstTail->MoveTail(FirstTail, PreviousLocation);
		
	/*for (auto Tail: Tails)
	{
		// Move to last position of the previous one 
		Tail->CurrentLocation = Tail->GetActorLocation();
		Tail->SetActorLocation(PreviousLocation);
		PreviousLocation = Tail->CurrentLocation;
	}*/

	bCanPress = true;
}

void ASnakeHead::CrossBorder()
{	
	FVector NewLocation = GetActorLocation();

	// If it's outside the board, move it to opposite side
	// Bottom border
	if (NewLocation.X <= Board->BoardRow * -100)
	{
		SetActorLocation(FVector(0, NewLocation.Y, 0));
	}
	// Upper border
	else if (NewLocation.X > 0)
	{
		SetActorLocation(FVector((Board->BoardRow - 1) * -100, NewLocation.Y, 0));
	}
	// Right border
	else if (NewLocation.Y >= Board->BoardColumn * 100)
	{
		SetActorLocation(FVector(NewLocation.X, 0, 0));
	}
	// Left border
	else if (NewLocation.Y < 0)
	{
		SetActorLocation(FVector(NewLocation.X, (Board->BoardRow - 1) * 100, 0));
	}
}

void ASnakeHead::PlayerAteFruit()
{
	MoveRate -= DecreaseRate;
	MoveRate = FMath::Clamp(MoveRate, 0.1f, MoveRate);
	PrimaryActorTick.TickInterval = MoveRate;

	AddTail();
}

void ASnakeHead::PlayerHitTail()
{
	// Head dead
	SnakeHead->SetMaterial(0, DeadMaterial);

	// Tails dead
	DeadTails(FirstTail);
	/*for (auto Tail: Tails)
	{
		Tail->SnakeDead(DeadMaterial);
	}*/
	
	UGameplayStatics::SetGamePaused(this, true);
}

void ASnakeHead::MoveUp()
{
	if (IsMovingDown() || !bCanPress) return;

	bCanPress = false;
	MoveDirection = FVector(1, 0, 0);
}

void ASnakeHead::MoveDown()
{
	if (IsMovingUp() || !bCanPress) return;

	bCanPress = false;
	MoveDirection = FVector(-1 , 0, 0);
}

void ASnakeHead::MoveRight()
{
	if (IsMovingLeft() || !bCanPress) return;

	bCanPress = false;
	MoveDirection = FVector(0, 1, 0);
}

void ASnakeHead::MoveLeft()
{
	if (IsMovingRight() || !bCanPress) return;

	bCanPress = false;
	MoveDirection = FVector(0, -1, 0);
}

bool ASnakeHead::IsMovingUp() const
{
	return MoveDirection == FVector(1, 0, 0);
}

bool ASnakeHead::IsMovingDown() const
{
	return MoveDirection == FVector(-1, 0, 0);
}

bool ASnakeHead::IsMovingRight() const
{
	return MoveDirection == FVector(0, 1, 0);
}

bool ASnakeHead::IsMovingLeft() const
{
	return MoveDirection == FVector(0, -1, 0);
}

void ASnakeHead::AddTail()
{
	// Reverse direction of moving direction
	FVector TailLocation = GetActorLocation() - MoveDirection * StepSize;

	auto NewTail = GetWorld()->SpawnActor<ASnakeTail>(TailClass, TailLocation, FRotator(0, 0, 0));
	//NewTail->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	NewTail->SnakeHead = this;

	// Add to linked list
	if (FirstTail == nullptr)
	{
		FirstTail = NewTail;
		LastTail = NewTail;
	}
	else
	{
		// NextTail of old LastTail is NewTail
		LastTail->NextTail = NewTail;
		// And LastTail will be NewTail
		LastTail = NewTail;
	}
	
	// Add to array
	//Tails.Add(Tail);
}

void ASnakeHead::DeadTails(ASnakeTail* IteratingTail)
{
	if (IteratingTail != nullptr)
	{
		IteratingTail->TailDead(DeadMaterial);

		DeadTails(IteratingTail->NextTail);
	}
}


