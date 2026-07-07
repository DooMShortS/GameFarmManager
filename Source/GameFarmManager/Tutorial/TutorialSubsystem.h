// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TutorialSubsystem.generated.h"

class UTutorialBeatData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTutorialBeatChanged, UTutorialBeatData*, NewBeat);

/**
 *  Tracks story tutorial progress: the active beat sequence, current beat index, and completion.
 *  Beat content (dialog, level content) is provided by the tutorial GameMode; this subsystem
 *  only tracks progress so it survives level travel within the tutorial.
 */
UCLASS()
class GAMEFARMMANAGER_API UTutorialSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	/** Ordered beats for the active tutorial playthrough */
	UPROPERTY(BlueprintReadOnly, Category="Tutorial")
	TArray<TObjectPtr<UTutorialBeatData>> Beats;

	/** Index of the current beat; INDEX_NONE if no tutorial is active, >= Beats.Num() once complete */
	UPROPERTY(BlueprintReadOnly, Category="Tutorial")
	int32 CurrentBeatIndex = INDEX_NONE;

public:

	/** Broadcast whenever the current beat changes; NewBeat is null once the tutorial completes */
	UPROPERTY(BlueprintAssignable, Category="Tutorial")
	FOnTutorialBeatChanged OnBeatChanged;

	/** Starts the tutorial with the given ordered beat sequence */
	UFUNCTION(BlueprintCallable, Category="Tutorial")
	void StartTutorial(const TArray<UTutorialBeatData*>& InBeats);

	/** Advances to the next beat. Returns false if there was no next beat (tutorial is now complete) */
	UFUNCTION(BlueprintCallable, Category="Tutorial")
	bool AdvanceBeat();

	/** Returns the currently active beat, or nullptr if none is active */
	UFUNCTION(BlueprintPure, Category="Tutorial")
	UTutorialBeatData* GetCurrentBeat() const;

	/** True once every beat has been advanced past */
	UFUNCTION(BlueprintPure, Category="Tutorial")
	bool IsTutorialComplete() const;
};
