// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Public/CustomeEvents.h"
#include "EventsResolvingPlayerController.generated.h"



UCLASS()
class AEventsResolvingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEventsResolvingPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	///Events 
	/** Jumping event */
	FOnJump OnJump;

	class AEventsResolvingCharacter* My_Pawn;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	FORCEINLINE void InvokeJump();
	FORCEINLINE void DoJump() const;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void BeginPlay() override;
};


