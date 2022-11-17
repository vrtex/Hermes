// Fill out your copyright notice in the Description page of Project Settings.


#include "HermesMessengerComponent.h"

#include "HermesMessenger.h"


UHermesMessengerComponent::UHermesMessengerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Messenger = CreateDefaultSubobject<UHermesMessenger>(TEXT("Messenger"));
}
