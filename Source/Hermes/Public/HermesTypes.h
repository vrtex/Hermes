// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HermesTypes.generated.h"

class UHermesMessenger;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FHermesMessengerInfo
{
	GENERATED_BODY()
public:
	// should always point to owning messenger
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UHermesMessenger> Self;
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Avatar;
};

USTRUCT(BlueprintType)
struct FHermesEventHandle
{
	GENERATED_BODY()
	friend class UHermesMessenger;

	FHermesEventHandle() = default;
	bool IsValid() const { return OwningMessenger.IsValid() && Tag.IsValid() && Handle.IsValid(); }

private:
	TWeakObjectPtr<UHermesMessenger> OwningMessenger;
	FGameplayTag Tag;
	bool bExactTag = true;
	FDelegateHandle Handle;
};