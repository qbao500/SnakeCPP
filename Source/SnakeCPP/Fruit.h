// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fruit.generated.h"

class ASnakeHead;
class AAIHead;
class ABoard;

UCLASS()
class SNAKECPP_API AFruit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFruit();

	UPROPERTY()
	ABoard* BoardRef;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* FruitMesh;

	UPROPERTY()
	ASnakeHead* SnakeHead;

	UPROPERTY()
	AAIHead* AIHead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void ChangeLocation();

private:
	UFUNCTION()
    void OnSnakeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

