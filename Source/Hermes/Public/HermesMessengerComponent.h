// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessengerInterface.h"
#include "Components/ActorComponent.h"
#include "HermesMessengerComponent.generated.h"

// messenger wrapped in a component
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HERMES_API UHermesMessengerComponent : public UActorComponent, public IHermesMessengerInterface
{
	GENERATED_BODY()

	UHermesMessengerComponent();

	virtual void OnRegister() override;

public:
	virtual UHermesMessenger* GetHermesMessenger_Implementation() const override { return Messenger; }

protected:

	virtual UHermesMessenger* CreateMessengerObject();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHermesMessenger> MessengerClass;
	
private:

	UPROPERTY()
	UHermesMessenger* Messenger;
	
};
