// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SendHermesMessage.h"

#include "HermesMessageTranslator.h"
#include "HermesMessenger.h"
#include "HermesUtilities.h"
#include "Animation/HermesAnimNotifyData.h"


void UAnimNotify_SendHermesMessage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if(!ValidateHermesNotify(MeshComp))
		return;

	UHermesMessenger* Messenger = UHermesUtilities::GetHermesMessenger(MeshComp->GetOwner());
	if(!Messenger)
		return;

	if(MessageCreatorClass.IsNull())
	{
		Messenger->SendMessage(MessageToSend);
		return;
	}
	
	FHermesMessage MetaMessage;
	const TSharedRef<FHermesAnimNotifyData> AnimData = MakeShared<FHermesAnimNotifyData>();
	AnimData->AnimNotify = this;
	AnimData->AnimSequence = Animation;
	AnimData->SkeletalMeshComponent = MeshComp;
	AnimData->NotifyEventReference = &EventReference;
	MetaMessage.AdditionalData = AnimData;

	Messenger->SendMessage(UHermesMessageTranslator::InvokeMessageTranslator(MetaMessage, MessageCreatorClass.LoadSynchronous()));
}

bool UAnimNotify_SendHermesMessage::ValidateHermesNotify(const USkeletalMeshComponent* MeshComponent)
{
	const UWorld* World = MeshComponent ? MeshComponent->GetWorld() : nullptr;
	return World && World->IsGameWorld();
}

#if WITH_EDITOR
bool UAnimNotify_SendHermesMessage::CanEditChange(const FProperty* InProperty) const
{
	if(!Super::CanEditChange(InProperty))
		return false;

	if(InProperty && InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UAnimNotify_SendHermesMessage, MessageToSend) && !MessageCreatorClass.IsNull())
		return false;

	return true;
}
#endif
