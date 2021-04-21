// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class ACell;
class AFruit;

UCLASS()
class SNAKECPP_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor'ws properties
	ABoard();
	
	UPROPERTY(EditDefaultsOnly)
	int32 BoardRow = 15;

	UPROPERTY(EditDefaultsOnly)
	int32 BoardColumn = 15;
	
	UPROPERTY()
	AFruit* FruitRef;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACell> CellClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFruit> FruitClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GenerateBoard();

	void SpawnFruit();
};
