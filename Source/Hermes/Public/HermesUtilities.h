// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
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


/**
 * 
 */
UCLASS()
class HERMES_API UHermesUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure)
	static UHermesMessenger* GetHermesMessenger(const UObject* RelayObject);

	UFUNCTION(BlueprintPure)
	static FHermesMessageDataHandle MakeHermesVector(const FVector& Vector);

	UFUNCTION(BlueprintCallable)
	static bool GetVectorFromMessage(const FHermesMessage& Msg, FVector& Vector);
	
};
