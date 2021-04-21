// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeTail.generated.h"

class ASnakeHead;

UCLASS()
class SNAKECPP_API ASnakeTail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeTail();
	
	UPROPERTY()
	ASnakeHead* SnakeHead;

	UPROPERTY()
	ASnakeTail* NextTail = nullptr;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TailMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void MoveTail(ASnakeTail* IteratingTail, FVector PreviousLocation);

	void TailDead(UMaterial* DeadMat);

private:
	UFUNCTION()
    void OnSnakeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
