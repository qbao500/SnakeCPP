// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeCPPGameModeBase.generated.h"

/**
 * 
 */

class ABoard;
class ASnakeHead;

UCLASS()
class SNAKECPP_API ASnakeCPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	ABoard* BoardRef;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABoard> BoardClass;

	void SpawnBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
