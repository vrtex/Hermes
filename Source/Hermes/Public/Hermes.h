// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHermes, Log, All)

class HERMES_API FHermesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	static void CheckHermesStructs(FName OnlyCheckModule);
	static void AfterModuleChange(FName ModuleName, EModuleChangeReason ModuleChangeReason);
	static TSet<FName> CheckedModules;
};
