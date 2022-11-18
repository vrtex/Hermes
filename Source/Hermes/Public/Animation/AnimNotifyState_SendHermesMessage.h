// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UObject/Object.h"
#include "AnimNotifyState_SendHermesMessage.generated.h"

class UAnimNotifyState_SendHermesMessage;
class UHermesMessageTranslator;
USTRUCT()
struct FHermesAnimNotifyStateMessageConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FHermesMessage MessageToSend;

	// int in meta message: 0 for begin, 1 for tick, 2 for end
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UHermesMessageTranslator> MessageTranslatorClass;

	void Send(int32 PhaseInt, const UAnimNotifyState_SendHermesMessage* Notify, USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const float* FloatData, const FAnimNotifyEventReference& EventReference) const;
};


/**
 * 
 */
UCLASS()
class HERMES_API UAnimNotifyState_SendHermesMessage : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bSendOnBegin = true;
	
	UPROPERTY(EditAnywhere)
	bool bSendOnEnd = true;

	UPROPERTY(EditAnywhere)
	bool bSendOnTick = false;

	UPROPERTY(EditAnywhere)
	FHermesAnimNotifyStateMessageConfig BeginMessage;
	
	UPROPERTY(EditAnywhere)
	FHermesAnimNotifyStateMessageConfig TickMessage;
	
	UPROPERTY(EditAnywhere)
	FHermesAnimNotifyStateMessageConfig EndMessage;
};
