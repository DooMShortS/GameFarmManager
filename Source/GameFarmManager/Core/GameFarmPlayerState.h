// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameFarmPlayerState.generated.h"

/**
 *  PlayerState for the GameFarm gameplay layer.
 */
UCLASS()
class GAMEFARMMANAGER_API AGameFarmPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	/** Constructor */
	AGameFarmPlayerState();
};
