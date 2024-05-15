// Copyright Marcode Aulinux


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

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

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for SERVER
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for CLIENT
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
