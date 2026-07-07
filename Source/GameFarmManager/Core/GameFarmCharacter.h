// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFarmManagerCharacter.h"
#include "GameFarmCameraManager.h"
#include "GameFarmCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;

/**
 *  Character for the GameFarm gameplay layer.
 *  Extends the first person template character with a third person camera rig
 *  used for the first/third person view toggle.
 */
UCLASS(abstract)
class GAMEFARMMANAGER_API AGameFarmCharacter : public AGameFarmManagerCharacter
{
	GENERATED_BODY()

	/** Spring arm for the third person camera; only active while in third person view */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* ThirdPersonSpringArm;

	/** Third person camera; only active while in third person view */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCameraComponent;

protected:

	/** Toggle Camera Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ToggleCameraAction;

public:

	/** Constructor */
	AGameFarmCharacter();

	/** Activates the camera and mesh visibility for the given view mode; called by the camera manager */
	void SetCameraViewMode(EGameFarmCameraViewMode NewViewMode);

protected:

	/** Called from Input Action to toggle between first and third person view */
	void DoToggleCameraView();

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:

	/** Returns the third person camera component */
	UCameraComponent* GetThirdPersonCameraComponent() const { return ThirdPersonCameraComponent; }
};
