// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFarmCameraManager.h"

AGameFarmCameraManager::AGameFarmCameraManager()
{
	// stub
}

void AGameFarmCameraManager::SetViewMode(EGameFarmCameraViewMode NewViewMode)
{
	if (CurrentViewMode == NewViewMode)
	{
		return;
	}

	CurrentViewMode = NewViewMode;
	OnViewModeChanged(NewViewMode);
}

void AGameFarmCameraManager::OnViewModeChanged_Implementation(EGameFarmCameraViewMode NewViewMode)
{
	// stub
}
