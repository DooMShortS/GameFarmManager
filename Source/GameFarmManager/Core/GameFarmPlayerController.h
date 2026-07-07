// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFarmManagerPlayerController.h"
#include "GameFarmPlayerController.generated.h"

/**
 *  PlayerController for the GameFarm gameplay layer.
 *  Extends the first person template PlayerController and uses the GameFarm camera manager.
 */
UCLASS(abstract, config="Game")
class GAMEFARMMANAGER_API AGameFarmPlayerController : public AGameFarmManagerPlayerController
{
	GENERATED_BODY()

public:

	/** Constructor */
	AGameFarmPlayerController();
};
