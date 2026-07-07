// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FarmWorldProfile.generated.h"

/** Road vs footpath spline in a farm world profile */
UENUM(BlueprintType)
enum class EFarmPathType : uint8
{
	Road,
	Footpath
};

/** A single road or footpath spline, defined in map space */
USTRUCT(BlueprintType)
struct FFarmSplinePath
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farm")
	EFarmPathType PathType = EFarmPathType::Footpath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farm")
	TArray<FVector2D> Points;
};

/**
 *  Serialized output of the Farm World Generator: everything needed to bake and reload
 *  one player-authored farm. Saved to its own slot; the slot name is indexed in the
 *  player's UGameFarmSaveGame::FarmProfileSlotNames library.
 */
UCLASS()
class GAMEFARMMANAGER_API UFarmWorldProfile : public USaveGame
{
	GENERATED_BODY()

public:

	/** Constructor */
	UFarmWorldProfile();

	/** Display name for this farm, shown in the player's farm library */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farm")
	FString FarmName;

	/** IDs of the biome zones the player selected for this farm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farm")
	TArray<FName> SelectedZoneIDs;

	/** Closed polygon outline defining the legal build/hunt boundary, in map space */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farm")
	TArray<FVector2D> PerimeterPoints;

	/** Road and footpath splines, in map space */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farm")
	TArray<FFarmSplinePath> Paths;

	/** Seed driving deterministic procedural scatter (trees, rocks, water features) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farm")
	int32 RandomSeed = 0;

	/** Farmhouse placement, in map space (baked to a world transform at bake time) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farm")
	FTransform FarmhouseTransform;
};
