// Fill out your copyright notice in the Description page of Project Settings.


#include "HermesUtilities.h"

#include "HermesMessenger.h"
#include "HermesMessengerInterface.h"

UHermesMessenger* UHermesUtilities::GetHermesMessenger(const UObject* RelayObject)
{
	return RelayObject && RelayObject->Implements<UHermesMessengerInterface>() ? IHermesMessengerInterface::Execute_GetHermesMessenger(RelayObject) : nullptr;
}

bool UHermesUtilities::SendHermesMessage(const UObject* RelayObject, const FHermesMessage& Message, FHermesMessage& ResponseMessage)
{
	UHermesMessenger* HermesMessenger = GetHermesMessenger(RelayObject);
	if(HermesMessenger)
		ResponseMessage = HermesMessenger->SendMessage(Message);
	return HermesMessenger != nullptr;
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

