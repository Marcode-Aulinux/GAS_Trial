// Copyright Marcode Aulinux


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	// set bOrientRotationToMovement to true so that character rotates to the direction of movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// set RotationRate to 400.0f so that character can rotate smoothly 400 degrees per second
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// set bConstrainToPlane to true so that character can only move in the plane
	GetCharacterMovement()->bConstrainToPlane = true;
	// set bSnapToPlaneAtStart to true so that character is snapped to the plane at the start
	// if character is not on ground, it will be moved to the ground
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// set bUseControllerRotationPitch to false so that character does not rotate on pitch
	bUseControllerRotationPitch = false;
	// set bUseControllerRotationRoll to false so that character does not rotate on roll
	bUseControllerRotationRoll = false;
	// set bUseControllerRotationYaw to false so that character does not rotate on yaw
	bUseControllerRotationYaw = false;
}
