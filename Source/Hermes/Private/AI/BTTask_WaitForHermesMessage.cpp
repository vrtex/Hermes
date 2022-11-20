// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_WaitForHermesMessage.h"

#include "AIController.h"
#include "HermesUtilities.h"

UBTTask_WaitForHermesMessage::UBTTask_WaitForHermesMessage()
{
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_WaitForHermesMessage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UHermesMessenger* HermesMessenger = GetMessenger(OwnerComp);
	if(!HermesMessenger)
		return EBTNodeResult::Failed;


	const TWeakObjectPtr<UBehaviorTreeComponent> ComponentPtr = &OwnerComp;
	const TWeakObjectPtr<UBTTask_WaitForHermesMessage> NodePtr = this;
	const FDelegateHandle DelegateHandle = HermesMessenger->GetDelegateForMessageTag(MessageTag, bExactTag).AddStatic(&UBTTask_WaitForHermesMessage::MessageCallback, NodePtr, ComponentPtr);
	
	FBTWaitForHermesMessageMemory* InstanceData = CastInstanceNodeMemory<FBTWaitForHermesMessageMemory>(NodeMemory);
	InstanceData->DelegateHandle = DelegateHandle;
	
	return EBTNodeResult::InProgress;
}

void UBTTask_WaitForHermesMessage::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	if(UHermesMessenger* HermesMessenger = GetMessenger(OwnerComp))
	{
		FBTWaitForHermesMessageMemory* InstanceData = CastInstanceNodeMemory<FBTWaitForHermesMessageMemory>(NodeMemory);
		HermesMessenger->GetDelegateForMessageTag(MessageTag, bExactTag).Remove(InstanceData->DelegateHandle);
		InstanceData->DelegateHandle.Reset();
	}
}

uint16 UBTTask_WaitForHermesMessage::GetInstanceMemorySize() const
{
	return sizeof(FBTWaitForHermesMessageMemory);
}

uint16 UBTTask_WaitForHermesMessage::GetSpecialMemorySize() const
{
	return sizeof(FBTWaitForHermesMessageMemory);
}

UHermesMessenger* UBTTask_WaitForHermesMessage::GetMessenger(const UBehaviorTreeComponent& OwnerComp)
{
	const AAIController* Controller = OwnerComp.GetAIOwner();
	const APawn* Pawn = Controller ? Controller->GetPawn() : nullptr;
	return UHermesUtilities::GetHermesMessenger(Pawn);
}

void UBTTask_WaitForHermesMessage::MessageCallback(UHermesMessenger* Messenger, const FHermesMessage* Message, TWeakObjectPtr<UBTTask_WaitForHermesMessage> Node, TWeakObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent)
{
	const UBTTaskNode* TemplateNode = static_cast<UBTTaskNode*>(BehaviorTreeComponent->FindTemplateNode(Node.Get()));
	BehaviorTreeComponent->OnTaskFinished(TemplateNode, EBTNodeResult::Succeeded);
}
