// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "EventsResolvingPlayerController.h"
#include "CustomeEvents.h"
#include "Processor.generated.h"


class AEventsResolvingPlayerController;
/**
 * 
 */
UCLASS()
class EVENTSRESOLVING_API UProcessor : public UObject
{
	GENERATED_BODY()
private:
public:
	void JumpMe(AEventsResolvingPlayerController* inPlayerController);
	void SetEventBinding(FOnJump& OnJumpEvent);
	
	
};




