// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFarmManagerCameraManager.h"
#include "GameFarmCameraManager.generated.h"

/** First person / third person view mode */
UENUM(BlueprintType)
enum class EGameFarmCameraViewMode : uint8
{
	FirstPerson,
	ThirdPerson
};

/**
 *  GameFarm camera manager.
 *  Tracks the active first person / third person view mode.
 */
UCLASS()
class GAMEFARMMANAGER_API AGameFarmCameraManager : public AGameFarmManagerCameraManager
{
	GENERATED_BODY()

protected:

	/** Currently active camera view mode */
	UPROPERTY(BlueprintReadOnly, Category="Camera")
	EGameFarmCameraViewMode CurrentViewMode = EGameFarmCameraViewMode::FirstPerson;

public:

	/** Constructor */
	AGameFarmCameraManager();

	/** Switches between first person and third person view modes */
	UFUNCTION(BlueprintCallable, Category="Camera")
	void SetViewMode(EGameFarmCameraViewMode NewViewMode);

	/** Returns the current camera view mode */
	UFUNCTION(BlueprintPure, Category="Camera")
	EGameFarmCameraViewMode GetViewMode() const { return CurrentViewMode; }

protected:

	/** Called when the view mode changes; override in Blueprint to drive camera blending */
	UFUNCTION(BlueprintNativeEvent, Category="Camera")
	void OnViewModeChanged(EGameFarmCameraViewMode NewViewMode);
	virtual void OnViewModeChanged_Implementation(EGameFarmCameraViewMode NewViewMode);
};
