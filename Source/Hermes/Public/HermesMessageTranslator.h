// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
#include "UObject/Object.h"
#include "HermesMessageTranslator.generated.h"

/**
 * helper class for creating message from a static context
 * can be used through CDO
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class HERMES_API UHermesMessageTranslator : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FHermesMessage TranslateMessage(const FHermesMessage& OriginalMessage) const;

	static FHermesMessage InvokeMessageTranslator(const FHermesMessage& OriginalMessage, const TSubclassOf<UHermesMessageTranslator>& TranslatorClass);
};

// useful when you need to produce a message through a translator and you need the original message
UCLASS()
class UHermesMessageTranslator_PassThrough : public UHermesMessageTranslator
{
	GENERATED_BODY()
public:
	virtual FHermesMessage TranslateMessage_Implementation(const FHermesMessage& OriginalMessage) const override { return OriginalMessage; }
};
