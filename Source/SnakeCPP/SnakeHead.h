// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakeHead.generated.h"

class UCameraComponent;
class ASnakeTail;
class ABoard;

UCLASS()
class SNAKECPP_API ASnakeHead : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakeHead();

	UPROPERTY()
	ABoard* Board;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SnakeHead;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeTail> TailClass;

	// Head of linked list of tails
	UPROPERTY(VisibleInstanceOnly)
	ASnakeTail* FirstTail = nullptr;

	// Tail of linked list
	UPROPERTY(VisibleInstanceOnly)
	ASnakeTail* LastTail = nullptr;

	/*UPROPERTY(VisibleInstanceOnly)
	TArray<ASnakeTail*> Tails;*/

	UPROPERTY(VisibleInstanceOnly)
	FVector MoveDirection = FVector(0, 1, 0);

	UPROPERTY(VisibleInstanceOnly)
	float StepSize = 100;
	
	UPROPERTY(EditAnywhere)
	float MoveRate = 0.3f;		// Decrease tick interval

	UPROPERTY(EditAnywhere)
	float DecreaseRate = 0.01f;

	UPROPERTY(VisibleInstanceOnly)
	FVector PreviousLocation;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* DeadMaterial;

	bool bCanPress = true;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PlayerAteFruit();

	void PlayerHitTail();

protected:
	// Move logic
	virtual void MainMovement();
	void CrossBorder();
	
	// Move input
	void MoveUp();
	void MoveDown();	
	void MoveRight();
	void MoveLeft();

	// Check move direction
	bool IsMovingUp() const;
	bool IsMovingDown() const;	
	bool IsMovingRight() const;
	bool IsMovingLeft() const;

	void AddTail();
	
	void DeadTails(ASnakeTail* IteratingTail);
};


