// Fill out your copyright notice in the Description page of Project Settings.


#include "HermesStructsChecker.h"

#include "Hermes.h"
#include "HermesMessage.h"

bool FHermesStructsChecker::Check(FName OnlyFromModule)
{
	const UScriptStruct* BaseStruct = FHermesMessageData::StaticStruct();
	const FString BaseStructName = BaseStruct->GetName();
	bool bResult = true;

	for(TObjectIterator<UScriptStruct> StructIter; StructIter; ++StructIter)
	{
		const UStruct* Struct = *StructIter;
		if(Struct == BaseStruct || !Struct->IsChildOf(BaseStruct))
			continue;

		if(OnlyFromModule != NAME_None)
		{
			FString StructPath = Struct->GetPathName();
			const FString ModulePattern = FString::Join(TArray<FString>{"/", OnlyFromModule.ToString(), "."}, TEXT(""));
			if(!StructPath.Contains(ModulePattern))
				continue;
		}

		const UScriptStruct* ScriptStruct = nullptr;
		{
			FHermesMessageData* StructInstance = static_cast<FHermesMessageData*>(FMemory::Malloc(Struct->GetStructureSize()));
			ON_SCOPE_EXIT { FMemory::Free(StructInstance); };
			Struct->InitializeStruct(StructInstance);
			ScriptStruct = StructInstance->GetScriptStruct();
		}
		const bool bStructOk = ScriptStruct == Struct;
		if(!bStructOk)
		{
			UE_LOG(LogHermes, Error, TEXT("Found invalid struct, %s -> %s"), *Struct->GetName(), *ScriptStruct->GetName());
		}
		bResult &= bStructOk;
	}

	return bResult;
}
