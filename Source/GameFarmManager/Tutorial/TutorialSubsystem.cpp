// Copyright Epic Games, Inc. All Rights Reserved.

#include "TutorialSubsystem.h"
#include "TutorialBeatData.h"

void UTutorialSubsystem::StartTutorial(const TArray<UTutorialBeatData*>& InBeats)
{
	Beats.Reset();
	Beats.Append(InBeats);
	CurrentBeatIndex = Beats.Num() > 0 ? 0 : INDEX_NONE;

	OnBeatChanged.Broadcast(GetCurrentBeat());
}

bool UTutorialSubsystem::AdvanceBeat()
{
	if (Beats.Num() == 0 || IsTutorialComplete())
	{
		return false;
	}

	if (CurrentBeatIndex + 1 >= Beats.Num())
	{
		CurrentBeatIndex = Beats.Num();
		OnBeatChanged.Broadcast(nullptr);
		return false;
	}

	++CurrentBeatIndex;
	OnBeatChanged.Broadcast(GetCurrentBeat());
	return true;
}

UTutorialBeatData* UTutorialSubsystem::GetCurrentBeat() const
{
	return Beats.IsValidIndex(CurrentBeatIndex) ? Beats[CurrentBeatIndex] : nullptr;
}

bool UTutorialSubsystem::IsTutorialComplete() const
{
	return Beats.Num() > 0 && CurrentBeatIndex >= Beats.Num();
}
