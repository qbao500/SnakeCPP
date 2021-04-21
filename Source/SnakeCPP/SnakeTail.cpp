// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeTail.h"


#include "SnakeHead.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASnakeTail::ASnakeTail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tail Mesh"));
	SetRootComponent(TailMesh);
	TailMesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	TailMesh->CastShadow = false;
}

// Called when the game starts or when spawned
void ASnakeTail::BeginPlay()
{
	Super::BeginPlay();

	TailMesh->OnComponentBeginOverlap.AddDynamic(this, &ASnakeTail::OnSnakeOverlapBegin);

}

// Move current tail then tell next tail to move, until next tail is null
void ASnakeTail::MoveTail(ASnakeTail* IteratingTail, FVector PreviousLocation)
{
	if (IteratingTail != nullptr)
	{
		FVector OldLocation = IteratingTail->GetActorLocation();
		IteratingTail->SetActorLocation(PreviousLocation);

		// Move next tail
		MoveTail(IteratingTail->NextTail, OldLocation);
	}
}

void ASnakeTail::TailDead(UMaterial* DeadMat)
{
	TailMesh->SetMaterial(0, DeadMat);
}

void ASnakeTail::OnSnakeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == SnakeHead)
	{		
		SnakeHead->PlayerHitTail();	
	}
}

