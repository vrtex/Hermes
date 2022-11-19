// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
#include "Animation/HermesAnimNotifyData.h"
#include "HermesUtilities.generated.h"

class UHermesMessenger;

namespace HermesUtilities
{

	template<typename ResultType>
	const ResultType* CastHermesData(const FHermesMessageData* DataPtr)
	{
		if(!DataPtr) return nullptr;

		const UScriptStruct* DataScriptStruct = DataPtr->GetScriptStruct();
		
		if(DataScriptStruct != ResultType::StaticStruct())
			return nullptr;

		return static_cast<const ResultType*>(DataPtr);
	}
	
	template<typename ResultType>
	const ResultType* CastHermesData(const FHermesMessageDataHandle& DataHandle)
	{
		return DataHandle.IsValid() ? CastHermesData<ResultType>(DataHandle.Get()) : nullptr;
	}
}

// convenience macro for implementing BP getters for different hermes data types
// it can be plopped in a static getter with signature: bool(const FHermesMessage& Message, FHermesAnimNotifyData& HermesData) (names must match exactly);
#define HERMES_DATA_GETTER_IMPL(DataClass) {\
const DataClass* Data = HermesUtilities::CastHermesData<DataClass>(Message.AdditionalData);\
if(Data)\
	HermesData = *Data;\
return Data != nullptr;\
};


/**
 * 
 */
UCLASS()
class HERMES_API UHermesUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static UHermesMessenger* GetHermesMessenger(const UObject* RelayObject);

	// safe to call for any object as RelayObject
	// won't do anything it provided object doesn't have a messenger
	UFUNCTION(BlueprintCallable)
	static bool SendHermesMessage(const UObject* RelayObject, const FHermesMessage& Message, FHermesMessage& ResponseMessage);

	UFUNCTION(BlueprintPure)
	static bool IsHermesMessageValid(const FHermesMessage& Message) { return Message.IsValid(); }

	UFUNCTION(BlueprintPure)
	static FHermesMessageDataHandle MakeHermesVector(const FVector& Vector);
	
	UFUNCTION(BlueprintPure)
	static bool GetHermesAnimData(const FHermesMessage& Message, FHermesAnimNotifyData& HermesData);

	UFUNCTION(BlueprintPure)
	static bool GetHermesVectorData(const FHermesMessage& Message, FHermesMessageData_Vector& HermesData);

};
