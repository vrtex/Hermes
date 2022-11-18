// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_SendHermesMessage.h"

#include "HermesMessageTranslator.h"
#include "HermesMessenger.h"
#include "HermesUtilities.h"
#include "Animation/AnimNotify_SendHermesMessage.h"


void FHermesAnimNotifyStateMessageConfig::Send(const int32 PhaseInt, const UAnimNotifyState_SendHermesMessage* Notify, USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const float* FloatData,
                                               const FAnimNotifyEventReference& EventReference) const
{
	UHermesMessenger* HermesMessenger = UHermesUtilities::GetHermesMessenger(MeshComp->GetOwner());
	if(!HermesMessenger)
		return;

	if(MessageTranslatorClass.IsNull())
	{
		HermesMessenger->SendMessage(MessageToSend);
		return;
	}

	FHermesMessage MetaMessage;
	MetaMessage.IntData = PhaseInt;
	if(FloatData)
		MetaMessage.Magnitude = *FloatData;

	const TSharedRef<FHermesAnimNotifyData> AnimData = MakeShared<FHermesAnimNotifyData>();
	AnimData->NotifyState = Notify;
	AnimData->AnimSequence = Animation;
	AnimData->NotifyEventReference = &EventReference;
	AnimData->SkeletalMeshComponent = MeshComp;
	MetaMessage.AdditionalData = AnimData;

	HermesMessenger->SendMessage(UHermesMessageTranslator::InvokeMessageTranslator(MetaMessage, MessageTranslatorClass.LoadSynchronous()));
}

void UAnimNotifyState_SendHermesMessage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if(bSendOnBegin && UAnimNotify_SendHermesMessage::ValidateHermesNotify(MeshComp))
		BeginMessage.Send(0, this, MeshComp, Animation, &TotalDuration, EventReference);
}

void UAnimNotifyState_SendHermesMessage::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if(bSendOnTick && UAnimNotify_SendHermesMessage::ValidateHermesNotify(MeshComp))
		TickMessage.Send(1, this, MeshComp, Animation, &FrameDeltaTime, EventReference);
}

void UAnimNotifyState_SendHermesMessage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if(bSendOnEnd && UAnimNotify_SendHermesMessage::ValidateHermesNotify(MeshComp))
		EndMessage.Send(2, this, MeshComp, Animation, nullptr, EventReference);
}
