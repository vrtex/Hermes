// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "HermesMessage.generated.h"

class UHermesMessenger;
class IHermesMessengerInterface;

USTRUCT()
struct HERMES_API FHermesMessageData
{
	GENERATED_BODY()
public:
	virtual ~FHermesMessageData() = default;

	// this needs to always be overriden
	virtual UScriptStruct* GetScriptStruct() const { return FHermesMessageData::StaticStruct(); }
};

USTRUCT(BlueprintType)
struct FHermesMessageData_Vector : public FHermesMessageData
{
	GENERATED_BODY()

public:
	virtual UScriptStruct* GetScriptStruct() const override { return FHermesMessageData_Vector::StaticStruct(); }

	UPROPERTY(BlueprintReadWrite)
	FVector DataVector;
};

// this allows message data to be stored in a BP class
USTRUCT(BlueprintType)
struct HERMES_API FHermesMessageDataHandle
{
	GENERATED_BODY()

public:

	FHermesMessageDataHandle() = default;
	explicit FHermesMessageDataHandle(FHermesMessageData* DataPtr) { (*this) = DataPtr; }
	FHermesMessageDataHandle& operator=(FHermesMessageData* DataPtr) { Data = TSharedPtr<FHermesMessageData>(DataPtr);  return *this; }
	FHermesMessageDataHandle& operator=(const TSharedPtr<FHermesMessageData> DataPtr) { Data = DataPtr;  return *this; }
	
	bool IsValid() const { return Data.IsValid(); }
	explicit operator bool() const { return IsValid(); }

	const FHermesMessageData* Get() const { return IsValid() ? Data.Get() : nullptr; }
	const FHermesMessageData* operator*() const { return Get(); }

	const FHermesMessageData* operator->() const { return Get(); }

	FHermesMessageData* Get() { return IsValid() ? Data.Get() : nullptr; }
	FHermesMessageData* operator*() { return Get(); }

	FHermesMessageData* operator->() { return Get(); }

private:
	TSharedPtr<FHermesMessageData> Data;
};

USTRUCT(BlueprintType)
struct HERMES_API FHermesMessage
{
	GENERATED_BODY()

	FHermesMessage() = default;
	FHermesMessage(FGameplayTag Tag) :MessageTag(Tag) {}

	// messages that can be sent should always have a tag
	bool IsValid() const { return MessageTag.IsValid(); }

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag MessageTag;

	// additional tags that can be used to store additional data (not to be confused with MessageTag)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag MessageTags;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TWeakObjectPtr<UObject> OptionalObject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 IntData = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Magnitude = 0.f;

	UPROPERTY(BlueprintReadWrite)
	FHermesMessageDataHandle AdditionalData;
};
