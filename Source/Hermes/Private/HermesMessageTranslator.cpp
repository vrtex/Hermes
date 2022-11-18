// Fill out your copyright notice in the Description page of Project Settings.


#include "HermesMessageTranslator.h"

FHermesMessage UHermesMessageTranslator::TranslateMessage_Implementation(const FHermesMessage& OriginalMessage) const
{
	unimplemented();
	return OriginalMessage;
}

FHermesMessage UHermesMessageTranslator::InvokeMessageTranslator(const FHermesMessage& OriginalMessage, const TSubclassOf<UHermesMessageTranslator>& TranslatorClass)
{
	check(TranslatorClass);
	const UHermesMessageTranslator* TranslatorCDO = TranslatorClass.GetDefaultObject();
	return TranslatorCDO->TranslateMessage(OriginalMessage);
}
