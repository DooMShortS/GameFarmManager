// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFarmGameMode.h"
#include "GameFarmPlayerState.h"

AGameFarmGameMode::AGameFarmGameMode()
{
	PlayerStateClass = AGameFarmPlayerState::StaticClass();
}
