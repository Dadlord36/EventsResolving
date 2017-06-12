// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "EventsResolving.h"
#include "EventsResolvingGameMode.h"
#include "EventsResolvingPlayerController.h"
#include "EventsResolvingCharacter.h"
#include "Public/MyGameInstance.h"

AEventsResolvingGameMode::AEventsResolvingGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AEventsResolvingPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AEventsResolvingGameMode::BeginPlay()
{
	//auto const	MyGemeInstance = Cast<UMyGameInstance>(GetGameInstance());

	
}
