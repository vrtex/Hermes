// Fill out your copyright notice in the Description page of Project Settings.


#include "HermesUtilities.h"

#include "HermesMessengerInterface.h"

UHermesMessenger* UHermesUtilities::GetHermesMessenger(const UObject* RelayObject)
{
	return RelayObject && RelayObject->Implements<UHermesMessengerInterface>() ? IHermesMessengerInterface::Execute_GetHermesMessenger(RelayObject) : nullptr;
}

FHermesMessageDataHandle UHermesUtilities::MakeHermesVector(const FVector& Vector)
{
	FHermesMessageData_Vector* VectorData = new FHermesMessageData_Vector();
	VectorData->DataVector = Vector;
	return FHermesMessageDataHandle(VectorData);
}

bool UHermesUtilities::GetHermesAnimData(const FHermesMessage& Message, FHermesAnimNotifyData& HermesData)
{
	HERMES_DATA_GETTER_IMPL(FHermesAnimNotifyData)
}

bool UHermesUtilities::GetHermesVectorData(const FHermesMessage& Message, FHermesMessageData_Vector& HermesData)
{
	HERMES_DATA_GETTER_IMPL(FHermesMessageData_Vector)
}

