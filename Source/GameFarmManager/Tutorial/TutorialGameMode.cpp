// Copyright Epic Games, Inc. All Rights Reserved.

#include "TutorialGameMode.h"
#include "TutorialSubsystem.h"
#include "GameFarmSaveGame.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

ATutorialGameMode::ATutorialGameMode()
{
	// stub
}

void ATutorialGameMode::BeginPlay()
{
	Super::BeginPlay();

	// returning players who already finished the tutorial skip straight to the next map
	if (CurrentProfile && CurrentProfile->bTutorialComplete)
	{
		if (!NextMap.IsNull())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextMap);
		}
		return;
	}

	if (UTutorialSubsystem* TutorialSubsystem = GetGameInstance()->GetSubsystem<UTutorialSubsystem>())
	{
		TutorialSubsystem->StartTutorial(TutorialBeats);
	}
}

void ATutorialGameMode::AdvanceTutorial()
{
	if (UTutorialSubsystem* TutorialSubsystem = GetGameInstance()->GetSubsystem<UTutorialSubsystem>())
	{
		if (!TutorialSubsystem->AdvanceBeat())
		{
			CompleteTutorial();
		}
	}
}

void ATutorialGameMode::CompleteTutorial()
{
	if (CurrentProfile)
	{
		CurrentProfile->bTutorialComplete = true;
	}

	SaveProfile();

	if (!NextMap.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextMap);
	}
}
