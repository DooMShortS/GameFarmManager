// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFarmSaveGame.generated.h"

/**
 *  SaveGame for the GameFarm gameplay layer.
 */
UCLASS()
class GAMEFARMMANAGER_API UGameFarmSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	/** Constructor */
	UGameFarmSaveGame();
};
