// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
#include "HermesAnimNotifyData.generated.h"

class UAnimNotify_SendHermesMessage;
USTRUCT(BlueprintType)
struct FHermesAnimNotifyData : public FHermesMessageData
{
	GENERATED_BODY()

	virtual UScriptStruct* GetScriptStruct() const override { return FHermesAnimNotifyData::StaticStruct(); }

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<const UAnimNotify> AnimNotify;
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<const UAnimNotifyState> NotifyState;
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UAnimSequenceBase> AnimSequence;
	
	const FAnimNotifyEventReference* NotifyEventReference;
};
