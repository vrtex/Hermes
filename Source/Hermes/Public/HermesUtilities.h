// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
#include "UObject/Object.h"
#include "HermesUtilities.generated.h"

class UHermesMessenger;

namespace HermesUtilities
{
	
}


/**
 * 
 */
UCLASS()
class HERMES_API UHermesUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	
	UFUNCTION(BlueprintPure)
	static UHermesMessenger* GetHermesMessenger(const UObject* RelayObject);
};
