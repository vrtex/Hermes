// Fill out your copyright notice in the Description page of Project Settings.


#include "HermesMessenger.h"

UHermesMessenger::UHermesMessenger()
{
	MessengerInfo.Self = this;
}

FHermesMessage UHermesMessenger::SendMessage(const FHermesMessage& Message)
{
	if(!Message.IsValid())
		return FHermesMessage::EmptyMessage;
	
	const TSharedPtr<FHermesMessageDelegate> DelegatePtr = FindDelegateForMessageTag(Message.MessageTag);
	if(!DelegatePtr.IsValid())
		return FHermesMessage::EmptyMessage;

	const FHermesMessage Response = RespondToMessage(Message);
	
	// broadcasting the message might cause the delegate to be moved or removed, pin it locally
	const FHermesMessageDelegate* MulticastDelegate = DelegatePtr.Get();
	MulticastDelegate->Broadcast(this, &Message);

	return Response;
}

FHermesMessage UHermesMessenger::RespondToMessage_Implementation(const FHermesMessage& IncomingMessage)
{
	// this can be overriden to react to message without having to bind event to a delegate
	return FHermesMessage::EmptyMessage;
}

FHermesMessageDelegate& UHermesMessenger::GetDelegateForMessageTag(const FGameplayTag& Tag)
{
	const TSharedPtr<FHermesMessageDelegate>* DelegatePtr = BoundDelegates.Find(Tag);
	FHermesMessageDelegate* Delegate = DelegatePtr ? DelegatePtr->Get() : nullptr;
	if(!Delegate)
	{
		const TSharedPtr<FHermesMessageDelegate> NewDelegate = MakeShareable(new FHermesMessageDelegate());
		BoundDelegates.Add(Tag, NewDelegate);
		Delegate = NewDelegate.Get();
	}

	return *Delegate;
}

FHermesEventHandle UHermesMessenger::BindHermesEvent(const FGameplayTag& MessageTag, const FHermesMessageDynamicDelegate& Delegate)
{
	FHermesMessageDelegate& DelegateForMessageTag = GetDelegateForMessageTag(MessageTag);
	FDelegateHandle DelegateHandle = DelegateForMessageTag.AddUObject(this, &UHermesMessenger::BlueprintMessageCallback, Delegate);
	FHermesEventHandle Result;
	Result.OwningMessenger = this;
	Result.Handle = DelegateHandle;
	Result.Tag = MessageTag;
	
	return Result;
}

void UHermesMessenger::UnbindHermesEvent(FHermesEventHandle& EventHandle)
{
	if(EventHandle.OwningMessenger != this || !EventHandle.Handle.IsValid())
		return;

	const FDelegateHandle DelegateHandle = EventHandle.Handle;
	const FGameplayTag Tag = EventHandle.Tag;
	
	EventHandle.Handle.Reset();
	EventHandle.Tag = FGameplayTag::EmptyTag;
	EventHandle.OwningMessenger.Reset();

	const TSharedPtr<FHermesMessageDelegate> DelegatePtr = FindDelegateForMessageTag(Tag);
	if(!DelegatePtr.IsValid())
		return;
	
	DelegatePtr->Remove(DelegateHandle);
	if(!DelegatePtr->IsBound())
		BoundDelegates.Remove(Tag);
}

void UHermesMessenger::SetMessengerInfo(const FHermesMessengerInfo& NewInfo)
{
	MessengerInfo = NewInfo;
	
	// make sure nothing sets Self to anything else
	if(MessengerInfo.Self != this)
		MessengerInfo.Self = this;
}

const FHermesMessengerInfo& UHermesMessenger::GetMessengerInfo() const
{
	return MessengerInfo;
}

TSharedPtr<FHermesMessageDelegate> UHermesMessenger::FindDelegateForMessageTag(const FGameplayTag& Tag)
{
	TSharedPtr<FHermesMessageDelegate>* FoundDelegate = BoundDelegates.Find(Tag);
	return FoundDelegate ? *FoundDelegate : nullptr;
}


void UHermesMessenger::BlueprintMessageCallback(UHermesMessenger* Messenger, const FHermesMessage* Message, FHermesMessageDynamicDelegate Delegate)
{
	Delegate.ExecuteIfBound(Messenger, *Message);
}
