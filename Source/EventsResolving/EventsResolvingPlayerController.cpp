// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "EventsResolving.h"
#include "EventsResolvingPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "EventsResolvingCharacter.h"
#include "Public/MyGameInstance.h"
#include "Public/Processor.h"

AEventsResolvingPlayerController::AEventsResolvingPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AEventsResolvingPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AEventsResolvingPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AEventsResolvingPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AEventsResolvingPlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AEventsResolvingPlayerController::InvokeJump);
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AEventsResolvingPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AEventsResolvingPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AEventsResolvingPlayerController::OnResetVR);


}

void AEventsResolvingPlayerController::InvokeJump()
{
	My_Pawn->Jump();
	OnJump.Broadcast(this);
}

void AEventsResolvingPlayerController::DoJump() const
{
}

void AEventsResolvingPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AEventsResolvingPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AEventsResolvingCharacter* MyPawn = Cast<AEventsResolvingCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UNavigationSystem::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
			
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AEventsResolvingPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AEventsResolvingPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AEventsResolvingPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AEventsResolvingPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AEventsResolvingPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//OnJump.AddUObject(this, &AEventsResolvingPlayerController::DoJump);
	My_Pawn = Cast<AEventsResolvingCharacter>(GetPawn());
	auto const GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	GameInstance->GetProcessor()->SetEventBinding(OnJump);
}
