// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFarmGameMode.h"
#include "SoloGameMode.generated.h"

class UGameFarmSaveGame;

/**
 *  GameMode for offline solo play.
 *  Loads the player's profile save on start and auto-saves it on an interval.
 */
UCLASS(abstract)
class GAMEFARMMANAGER_API ASoloGameMode : public AGameFarmGameMode
{
	GENERATED_BODY()

protected:

	/** Seconds between automatic profile saves */
	UPROPERTY(EditAnywhere, Category="Save")
	float AutoSaveIntervalSeconds = 300.0f;

	/** The active player profile for this session */
	UPROPERTY(BlueprintReadOnly, Category="Save")
	TObjectPtr<UGameFarmSaveGame> CurrentProfile;

	FTimerHandle AutoSaveTimerHandle;

public:

	/** Constructor */
	ASoloGameMode();

protected:

	virtual void BeginPlay() override;

public:

	/** Loads the player profile from disk, creating a new one if none exists */
	UFUNCTION(BlueprintCallable, Category="Save")
	void LoadProfile();

	/** Saves the current player profile to disk */
	UFUNCTION(BlueprintCallable, Category="Save")
	void SaveProfile();

	/** Returns the active player profile */
	UFUNCTION(BlueprintPure, Category="Save")
	UGameFarmSaveGame* GetCurrentProfile() const { return CurrentProfile; }
};
