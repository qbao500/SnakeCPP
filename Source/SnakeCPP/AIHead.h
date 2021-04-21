// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeHead.h"
#include "AIHead.generated.h"

/**
 * Inherited from SnakeHead
 */
UCLASS()
class SNAKECPP_API AAIHead : public ASnakeHead
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleInstanceOnly)
	FVector FruitLocation;

private:
	bool bShouldDecide = true;

	// For line trace to check if going to hit tail
	FHitResult Hit;
	FCollisionQueryParams CollisionQueryParams;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MainMovement() override;

private:
	void DecideMovement();

	void CheckBorder();

	void CheckAhead();

	// Turn to safer direction
	void CheckTwoSides(FVector NewDirection);

	// Main line trace function
	bool LineTrace(FVector Start, FVector Direction = FVector(0, 0, 0), float Length = 100);
};
