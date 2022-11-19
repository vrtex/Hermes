// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
#include "HermesTypes.h"
#include "UObject/Object.h"
#include "HermesMessenger.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FHermesMessageDelegate, UHermesMessenger* Messenger, const FHermesMessage* Message);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FHermesMessageDynamicDelegate, UHermesMessenger*, Messenger, const FHermesMessage&, Message);


/**
 * 
 */
UCLASS(Blueprintable)
class HERMES_API UHermesMessenger : public UObject
{
	GENERATED_BODY()

public:

	UHermesMessenger();

	UFUNCTION(BlueprintCallable)
	FHermesMessage SendMessage(const FHermesMessage& Message);

	UFUNCTION(BlueprintNativeEvent)
	FHermesMessage RespondToMessage(const FHermesMessage& IncomingMessage);
	
	FHermesMessageDelegate& GetDelegateForMessageTag(const FGameplayTag& Tag);

	// events bound to empty tag will receive any message
	UFUNCTION(BlueprintCallable)
	FHermesEventHandle BindHermesEvent(const FGameplayTag& MessageTag, const FHermesMessageDynamicDelegate& Delegate);

	UFUNCTION(BlueprintCallable)
	void UnbindHermesEvent(UPARAM(ref) FHermesEventHandle& EventHandle);

	UFUNCTION(BlueprintCallable)
	void SetMessengerInfo(const FHermesMessengerInfo& NewInfo);
	
	UFUNCTION(BlueprintPure)
	const FHermesMessengerInfo& GetMessengerInfo() const;

private:

	// this differ from GetDelegateForMessageTag: if delegate isn't present it won't get created
	TSharedPtr<FHermesMessageDelegate> FindDelegateForMessageTag(const FGameplayTag& Tag);

	void BlueprintMessageCallback(UHermesMessenger* Messenger, const FHermesMessage* Message, FHermesMessageDynamicDelegate Delegate);

	TMap<FGameplayTag, TSharedPtr<FHermesMessageDelegate>> BoundDelegates;

	FHermesMessengerInfo MessengerInfo;

};

