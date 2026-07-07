// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFarmCameraManager.h"
#include "GameFarmCharacter.h"
#include "GameFramework/PlayerController.h"

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
	if (APlayerController* PC = GetOwningPlayerController())
	{
		if (AGameFarmCharacter* FarmCharacter = Cast<AGameFarmCharacter>(PC->GetPawn()))
		{
			FarmCharacter->SetCameraViewMode(NewViewMode);
		}
	}
}
