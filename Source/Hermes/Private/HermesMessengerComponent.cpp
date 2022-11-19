// Fill out your copyright notice in the Description page of Project Settings.


#include "HermesMessengerComponent.h"

#include "HermesMessenger.h"


UHermesMessengerComponent::UHermesMessengerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MessengerClass = UHermesMessenger::StaticClass();
}

void UHermesMessengerComponent::OnRegister()
{
	Super::OnRegister();
	Messenger = CreateMessengerObject();
	if(Messenger)
	{
		FHermesMessengerInfo HermesMessengerInfo = Messenger->GetMessengerInfo();
		HermesMessengerInfo.Avatar = GetOwner();
		Messenger->SetMessengerInfo(HermesMessengerInfo);
	}
}

UHermesMessenger* UHermesMessengerComponent::CreateMessengerObject()
{
	const UClass* Class = MessengerClass ? MessengerClass.Get() : UHermesMessenger::StaticClass();
	return NewObject<UHermesMessenger>(this, Class);
}
