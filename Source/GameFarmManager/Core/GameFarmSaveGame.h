// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFarmSaveGame.generated.h"

/**
 *  SaveGame for the GameFarm gameplay layer.
 *  Stores player profile-level state: tutorial progress and the player's farm library.
 */
UCLASS()
class GAMEFARMMANAGER_API UGameFarmSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	/** Constructor */
	UGameFarmSaveGame();

	/** Save slot name used for the player profile */
	static const FString ProfileSlotName;

	/** True once the player has completed the story tutorial */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Profile")
	bool bTutorialComplete = false;

	/** Save slot names of the player's saved farms, indexing their farm library */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Profile")
	TArray<FString> FarmProfileSlotNames;
};
