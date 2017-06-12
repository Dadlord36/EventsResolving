// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "EventsResolvingGameMode.generated.h"

UCLASS(minimalapi)
class AEventsResolvingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEventsResolvingGameMode();
protected:
	void BeginPlay() override;
};



