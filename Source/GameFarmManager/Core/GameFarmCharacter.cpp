// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFarmCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

AGameFarmCharacter::AGameFarmCharacter()
{
	// Third person spring arm and camera; disabled by default so they don't tick/render in first person
	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	ThirdPersonSpringArm->SetupAttachment(GetCapsuleComponent());
	ThirdPersonSpringArm->TargetArmLength = 300.0f;
	ThirdPersonSpringArm->SocketOffset = FVector(0.0f, 0.0f, 60.0f);
	ThirdPersonSpringArm->bUsePawnControlRotation = true;
	ThirdPersonSpringArm->SetActive(false);
	ThirdPersonSpringArm->SetComponentTickEnabled(false);

	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;
	ThirdPersonCameraComponent->SetActive(false);
}

void AGameFarmCharacter::SetCameraViewMode(EGameFarmCameraViewMode NewViewMode)
{
	const bool bThirdPerson = NewViewMode == EGameFarmCameraViewMode::ThirdPerson;

	// only tick/render the third person rig while it's the active view
	ThirdPersonSpringArm->SetComponentTickEnabled(bThirdPerson);
	ThirdPersonSpringArm->SetActive(bThirdPerson);
	ThirdPersonCameraComponent->SetActive(bThirdPerson);
	GetFirstPersonCameraComponent()->SetActive(!bThirdPerson);

	// show the full body to the owner in third person; hide the first person arms mesh
	GetMesh()->SetOwnerNoSee(!bThirdPerson);
	GetFirstPersonMesh()->SetOwnerNoSee(bThirdPerson);
}

void AGameFarmCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Started, this, &AGameFarmCharacter::DoToggleCameraView);
	}
}

void AGameFarmCharacter::DoToggleCameraView()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (AGameFarmCameraManager* FarmCameraManager = Cast<AGameFarmCameraManager>(PC->PlayerCameraManager))
		{
			const EGameFarmCameraViewMode NewMode = (FarmCameraManager->GetViewMode() == EGameFarmCameraViewMode::FirstPerson)
				? EGameFarmCameraViewMode::ThirdPerson
				: EGameFarmCameraViewMode::FirstPerson;

			FarmCameraManager->SetViewMode(NewMode);
		}
	}
}
