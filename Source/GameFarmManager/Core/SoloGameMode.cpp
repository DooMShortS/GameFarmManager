// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoloGameMode.h"
#include "GameFarmSaveGame.h"
#include "Kismet/GameplayStatics.h"

ASoloGameMode::ASoloGameMode()
{
	// stub
}

void ASoloGameMode::BeginPlay()
{
	Super::BeginPlay();

	LoadProfile();

	if (AutoSaveIntervalSeconds > 0.0f)
	{
		GetWorldTimerManager().SetTimer(AutoSaveTimerHandle, this, &ASoloGameMode::SaveProfile, AutoSaveIntervalSeconds, true);
	}
}

void ASoloGameMode::LoadProfile()
{
	if (UGameplayStatics::DoesSaveGameExist(UGameFarmSaveGame::ProfileSlotName, 0))
	{
		CurrentProfile = Cast<UGameFarmSaveGame>(UGameplayStatics::LoadGameFromSlot(UGameFarmSaveGame::ProfileSlotName, 0));
	}

	if (!CurrentProfile)
	{
		CurrentProfile = Cast<UGameFarmSaveGame>(UGameplayStatics::CreateSaveGameObject(UGameFarmSaveGame::StaticClass()));
	}
}

void ASoloGameMode::SaveProfile()
{
	if (CurrentProfile)
	{
		UGameplayStatics::SaveGameToSlot(CurrentProfile, UGameFarmSaveGame::ProfileSlotName, 0);
	}
}
