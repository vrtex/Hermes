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

bool UHermesUtilities::GetVectorFromMessage(const FHermesMessage& Msg, FVector& Vector)
{
	const FHermesMessageData_Vector* Data = HermesUtilities::CastHermesData<FHermesMessageData_Vector>(Msg.AdditionalData);
	if(Data)
		Vector = Data->DataVector;
	return Data != nullptr;
}
