// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TutorialBeatData.generated.h"

/**
 *  Data for a single beat in the story tutorial sequence.
 *  One asset per beat (e.g. arrive, walk boundary, spot wildlife, practice tool, handoff).
 */
UCLASS()
class GAMEFARMMANAGER_API UTutorialBeatData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/** Unique identifier for this beat, referenced by trigger volumes / interactions in the level */
	UPROPERTY(EditDefaultsOnly, Category="Tutorial")
	FName BeatID;

	/** Order index for this beat within the tutorial sequence */
	UPROPERTY(EditDefaultsOnly, Category="Tutorial")
	int32 BeatOrder = 0;

	/** Mentor dialog / subtitle text shown during this beat */
	UPROPERTY(EditDefaultsOnly, Category="Tutorial")
	FText DialogText;
};
