// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFarmManagerGameMode.h"
#include "GameFarmGameMode.generated.h"

/**
 *  GameMode for the GameFarm gameplay layer.
 *  Extends the first person template GameMode with GameFarm-specific defaults.
 */
UCLASS(abstract)
class GAMEFARMMANAGER_API AGameFarmGameMode : public AGameFarmManagerGameMode
{
	GENERATED_BODY()

public:
	AGameFarmGameMode();
};
