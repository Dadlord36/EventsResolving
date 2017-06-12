// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

class UProcessor;

UCLASS()
class EVENTSRESOLVING_API UMyGameInstance : public UGameInstance
{

	GENERATED_BODY()
private:
	UProcessor	*Processor;
public:
	UMyGameInstance();
	UProcessor* GetProcessor() ;
};


