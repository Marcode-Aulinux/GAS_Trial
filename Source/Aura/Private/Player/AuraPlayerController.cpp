// Copyright Marcode Aulinux


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	// Explanation: The Enhanced Input plugin is a plugin that allows you to create input mappings and contexts that can be used to bind actions to keys and buttons.
	UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	// cursor is not locked to the viewport and is visible
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeDatas;
	InputModeDatas.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeDatas.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeDatas);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// This method is analogous to setting up input listeners in Unity,
	// where you might subscribe to input events. Here,
	// it binds a specific action (like moving the player) to a function
	// that will be called when the input action occurs, using Unreal's enhanced input system.
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// This function is called when the MoveAction is triggered.
	// It gets the input vector from the action value and uses it to move the player.
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// GetControlRotation() returns the rotation of the controller.
	// This is used to determine the forward and right directions of the player.
	const FRotator Rotation = GetControlRotation();
	// YawRotation is a rotation that only contains the yaw component of the controller's rotation.
	// This is used to get the forward and right directions of the player.
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// GetPawn() returns the pawn that the controller is controlling.
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// AddMovementInput() adds movement in the specified direction.
		// The first parameter is the direction to move in, and the second parameter is the amount of movement.
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	// GetHitResultUnderCursor() gets the hit result under the cursor.
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	// Last and this actor are used to keep track of the last and current actors under the cursor.
	// Example: If the cursor is over an enemy, the enemy will be highlighted.
	// If the cursor moves to another enemy, the previous enemy will be unhighlighted and the new enemy will be highlighted.
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	 * Line trace from cursor. There are several scenarios:
	 * 1. LastActor is null and ThisActor is not null: Do nothing.
	 * 2. LostActor is null and ThisActor is valid: Highlight ThisActor.
	 * 3. LastActor is valid and ThisActor is null: Unhighlight LastActor.
	 * 4. Both actors are valid but different: Unhighlight LastActor and highlight ThisActor.
	 * 5. Both actors are valid and the same: Do nothing.
	 */

	if (LastActor == nullptr && ThisActor != nullptr)
	{
		// Case 2
		ThisActor->HighlightActor();
	}
	else if (LastActor != nullptr && ThisActor == nullptr)
	{
		// Case 3
		LastActor->UnHighlightActor();
	}
	else if (LastActor != nullptr && ThisActor != nullptr && LastActor != ThisActor)
	{
		// Case 4
		LastActor->UnHighlightActor();
		ThisActor->HighlightActor();
	}
}
