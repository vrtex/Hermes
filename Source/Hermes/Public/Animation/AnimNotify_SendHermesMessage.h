// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HermesMessage.h"
#include "AnimNotify_SendHermesMessage.generated.h"

class UHermesMessageTranslator;

/**
 * 
 */
UCLASS()
class HERMES_API UAnimNotify_SendHermesMessage : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	FHermesMessage MessageToSend;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UHermesMessageTranslator> MessageCreatorClass;

	static bool ValidateHermesNotify(const USkeletalMeshComponent* MeshComponent);

#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif
};
