// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFarmManagerCharacter.h"
#include "GameFarmCharacter.generated.h"

/**
 *  Character for the GameFarm gameplay layer.
 *  Extends the first person template character.
 */
UCLASS(abstract)
class GAMEFARMMANAGER_API AGameFarmCharacter : public AGameFarmManagerCharacter
{
	GENERATED_BODY()

public:

	/** Constructor */
	AGameFarmCharacter();
};
