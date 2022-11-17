// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
#include "UObject/Object.h"
#include "HermesMessenger.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FHermesMessageDelegate, UHermesMessenger* Messenger, const FHermesMessage* Message);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FHermesMessageDynamicDelegate, UHermesMessenger*, Messenger, const FHermesMessage&, Message);

USTRUCT(BlueprintType)
struct FHermesEventHandle
{
	GENERATED_BODY()
	friend class UHermesMessenger;

	FHermesEventHandle() = default;

private:
	TWeakObjectPtr<UHermesMessenger> OwningMessenger;
	FGameplayTag Tag;
	FDelegateHandle Handle;
};

/**
 * 
 */
UCLASS()
class HERMES_API UHermesMessenger : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SendMessage(const FHermesMessage& Message);
	
	FHermesMessageDelegate& GetDelegateForMessageTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	FHermesEventHandle BindHermesEvent(const FGameplayTag& MessageTag, const FHermesMessageDynamicDelegate& Delegate);

	UFUNCTION(BlueprintCallable)
	void UnbindHermesEvent(UPARAM(ref) FHermesEventHandle& EventHandle);

private:

	// this differ from GetDelegateForMessageTag: if delegate isn't present it won't get created
	TSharedPtr<FHermesMessageDelegate> FindDelegateForMessageTag(const FGameplayTag& Tag);


	void BlueprintMessageCallback(UHermesMessenger* Messenger, const FHermesMessage* Message, FHermesMessageDynamicDelegate Delegate);

	TMap<FGameplayTag, TSharedPtr<FHermesMessageDelegate>> BoundDelegates;

};

