// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SoloGameMode.h"
#include "TutorialGameMode.generated.h"

class UTutorialBeatData;

/**
 *  GameMode for the story tutorial sub-level.
 *  Starts the beat sequence on begin play, or skips straight to the next map if the
 *  player's profile already has the tutorial marked complete.
 */
UCLASS(abstract)
class GAMEFARMMANAGER_API ATutorialGameMode : public ASoloGameMode
{
	GENERATED_BODY()

protected:

	/** Ordered tutorial beats for this playthrough */
	UPROPERTY(EditAnywhere, Category="Tutorial")
	TArray<TObjectPtr<UTutorialBeatData>> TutorialBeats;

	/** Map to travel to once the tutorial is complete (the Farm World Generator, once it exists) */
	UPROPERTY(EditAnywhere, Category="Tutorial")
	TSoftObjectPtr<UWorld> NextMap;

public:

	/** Constructor */
	ATutorialGameMode();

protected:

	virtual void BeginPlay() override;

public:

	/** Advances the tutorial by one beat; completes the tutorial if that was the last beat */
	UFUNCTION(BlueprintCallable, Category="Tutorial")
	void AdvanceTutorial();

	/** Marks the tutorial complete on the player profile, saves, and travels to the next map */
	UFUNCTION(BlueprintCallable, Category="Tutorial")
	void CompleteTutorial();
};
