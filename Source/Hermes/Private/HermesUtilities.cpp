﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HermesUtilities.h"

#include "HermesMessengerInterface.h"

UHermesMessenger* UHermesUtilities::GetHermesMessenger(const UObject* RelayObject)
{
	return RelayObject && RelayObject->Implements<UHermesMessengerInterface>() ? IHermesMessengerInterface::Execute_GetHermesMessenger(RelayObject) : nullptr;
}
