// Fill out your copyright notice in the Description page of Project Settings.

#include "EventsResolving.h"
#include "Public/MyGameInstance.h"
#include "Public/Processor.h"


UMyGameInstance::UMyGameInstance()
{
	
}

UProcessor* UMyGameInstance::GetProcessor()
{
	if(Processor == nullptr)
		Processor = NewObject<UProcessor>();
	return Processor;
}
