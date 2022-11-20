// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WaitForHermesMessage.generated.h"


struct FHermesMessage;
class UHermesMessenger;

struct FBTWaitForHermesMessageMemory
{
	FDelegateHandle DelegateHandle;
};

/**
 * 
 */
UCLASS()
class HERMES_API UBTTask_WaitForHermesMessage : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTask_WaitForHermesMessage();

	UPROPERTY(EditAnywhere)
	FGameplayTag MessageTag;
	
	UPROPERTY(EditAnywhere)
	bool bExactTag = true;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	virtual uint16 GetInstanceMemorySize() const override;
	virtual uint16 GetSpecialMemorySize() const override;

	static UHermesMessenger* GetMessenger(const UBehaviorTreeComponent& OwnerComp);
	static void MessageCallback(UHermesMessenger* Messenger, const FHermesMessage* Message, TWeakObjectPtr<UBTTask_WaitForHermesMessage> Node, TWeakObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent);
};
