// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HermesMessengerInterface.generated.h"

class UHermesMessenger;
// This class does not need to be modified.
UINTERFACE()
class UHermesMessengerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HERMES_API IHermesMessengerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	UHermesMessenger* GetHermesMessenger() const;
};
