// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FarmWorldGeneratorSubsystem.generated.h"

class UFarmWorldProfile;

/**
 *  Holds the farm profile currently being authored (Zones -> Perimeter -> Farmhouse -> Roads
 *  -> Paths -> Seed -> Preview -> Save) and the validation / seeded scatter math the
 *  generator UI needs along the way. Does not touch Landscape/PCG/meshes - see FarmWorldBaker
 *  for turning a finished profile into an actual playable level.
 */
UCLASS()
class GAMEFARMMANAGER_API UFarmWorldGeneratorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	/** The farm profile currently being authored by the player */
	UPROPERTY(BlueprintReadOnly, Category="Farm")
	TObjectPtr<UFarmWorldProfile> WorkingProfile;

public:

	/** Starts authoring a new farm profile, replacing any in-progress one */
	UFUNCTION(BlueprintCallable, Category="Farm")
	UFarmWorldProfile* CreateNewProfile();

	/** Returns the profile currently being authored, or nullptr if none is active */
	UFUNCTION(BlueprintPure, Category="Farm")
	UFarmWorldProfile* GetWorkingProfile() const { return WorkingProfile; }

	/** True if the given point lies inside the closed perimeter polygon */
	UFUNCTION(BlueprintPure, Category="Farm")
	static bool IsPointInsidePerimeter(const FVector2D& Point, const TArray<FVector2D>& PerimeterPoints);

	/** Area enclosed by the perimeter polygon, in map-space units squared */
	UFUNCTION(BlueprintPure, Category="Farm")
	static float GetPerimeterArea(const TArray<FVector2D>& PerimeterPoints);

	/** True if the working profile's farmhouse lies inside its own perimeter */
	UFUNCTION(BlueprintPure, Category="Farm")
	bool ValidateFarmhousePlacement() const;

	/**
	 * Deterministic scatter points inside the working profile's perimeter, seeded from its
	 * RandomSeed. ScatterChannel offsets the seed so multiple independent passes (e.g. trees
	 * vs rocks) don't produce identical placement.
	 */
	UFUNCTION(BlueprintCallable, Category="Farm")
	TArray<FVector2D> GenerateScatterPoints(int32 Count, int32 ScatterChannel) const;

	/** Saves the working profile to the given farm library slot name */
	UFUNCTION(BlueprintCallable, Category="Farm")
	bool SaveWorkingProfile(const FString& SlotName);
};
