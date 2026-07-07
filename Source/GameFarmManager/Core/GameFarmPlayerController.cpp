// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFarmPlayerController.h"
#include "GameFarmCameraManager.h"

AGameFarmPlayerController::AGameFarmPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AGameFarmCameraManager::StaticClass();
}
