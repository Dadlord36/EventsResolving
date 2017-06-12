// Fill out your copyright notice in the Description page of Project Settings.

#include "EventsResolving.h"
#include "Public/Processor.h"


void UProcessor::SetEventBinding(FOnJump& OnJumpEvent)
{
	OnJumpEvent.AddUObject(this, &UProcessor::JumpMe);
}

void UProcessor::JumpMe(AEventsResolvingPlayerController* inPlayerController)
{
	UKismetSystemLibrary::PrintString(inPlayerController, " Was Jumped");
}
