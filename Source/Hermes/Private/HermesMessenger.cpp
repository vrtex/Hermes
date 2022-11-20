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
	
	const FHermesMessage Response = RespondToMessage(Message);

	BroadcastMessage(Message);

	return Response;
}

FHermesMessage UHermesMessenger::RespondToMessage_Implementation(const FHermesMessage& IncomingMessage)
{
	// this can be overriden to react to a message without having to bind event to a delegate
	return FHermesMessage::EmptyMessage;
}

FHermesMessageDelegate& UHermesMessenger::GetDelegateForMessageTag(const FGameplayTag& Tag, bool bExactTag)
{
	TMap<FGameplayTag, TSharedPtr<FHermesMessageDelegate>>& SourceMap = bExactTag ? BoundDelegates : BoundFilterDelegates;
	
	const TSharedPtr<FHermesMessageDelegate>* DelegatePtr = SourceMap.Find(Tag);
	FHermesMessageDelegate* Delegate = DelegatePtr ? DelegatePtr->Get() : nullptr;
	if(!Delegate)
	{
		const TSharedPtr<FHermesMessageDelegate> NewDelegate = MakeShareable(new FHermesMessageDelegate());
		SourceMap.Add(Tag, NewDelegate);
		Delegate = NewDelegate.Get();
	}

	return *Delegate;
}


FHermesEventHandle UHermesMessenger::BindHermesEvent(const FGameplayTag& MessageTag, const FHermesMessageDynamicDelegate& Delegate, bool bExactTag)
{
	FHermesMessageDelegate& DelegateForMessageTag = GetDelegateForMessageTag(MessageTag, bExactTag);
	const FDelegateHandle DelegateHandle = DelegateForMessageTag.AddUObject(this, &UHermesMessenger::BlueprintMessageCallback, Delegate);
	
	FHermesEventHandle Result;
	Result.OwningMessenger = this;
	Result.Handle = DelegateHandle;
	Result.bExactTag = bExactTag;
	Result.Tag = MessageTag;
	
	return Result;
}

void UHermesMessenger::UnbindHermesEvent(FHermesEventHandle& EventHandle)
{
	if(EventHandle.OwningMessenger != this || !EventHandle.Handle.IsValid())
		return;

	const FDelegateHandle DelegateHandle = EventHandle.Handle;
	const FGameplayTag Tag = EventHandle.Tag;

	TMap<FGameplayTag, TSharedPtr<FHermesMessageDelegate>>& DelegateMap = EventHandle.bExactTag ? BoundDelegates : BoundFilterDelegates;
	
	EventHandle.Handle.Reset();
	EventHandle.Tag = FGameplayTag::EmptyTag;
	EventHandle.OwningMessenger.Reset();

	if(!DelegateMap.Contains(Tag))
		return;

	const TSharedPtr<FHermesMessageDelegate> DelegatePtr = DelegateMap[Tag];
	if(!DelegatePtr.IsValid())
		return;
	
	DelegatePtr->Remove(DelegateHandle);
	if(!DelegatePtr->IsBound())
		DelegateMap.Remove(Tag);
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

void UHermesMessenger::BroadcastMessage(const FHermesMessage& Message)
{
	TSet<TSharedPtr<FHermesMessageDelegate>> DelegatesToBroadcast;
	
	for(const auto& [Tag, Delegate] : BoundDelegates)
	{
		if(Message.MessageTag == Tag)
			DelegatesToBroadcast.Add(Delegate);
	}

	for(const auto& [Tag, Delegate] : BoundFilterDelegates)
	{
		if(Tag == FGameplayTag::EmptyTag || Message.MessageTag.MatchesTag(Tag))
			DelegatesToBroadcast.Add(Delegate);
	}

	for(const TSharedPtr<FHermesMessageDelegate>& Delegate : DelegatesToBroadcast)
	{
		Delegate->Broadcast(this, &Message);
	}
	
}


void UHermesMessenger::BlueprintMessageCallback(UHermesMessenger* Messenger, const FHermesMessage* Message, FHermesMessageDynamicDelegate Delegate)
{
	Delegate.ExecuteIfBound(Messenger, *Message);
}
