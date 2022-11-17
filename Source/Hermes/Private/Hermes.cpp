// Copyright Epic Games, Inc. All Rights Reserved.

#include "Hermes.h"

#include "HermesStructsChecker.h"

#define LOCTEXT_NAMESPACE "FHermesModule"

DEFINE_LOG_CATEGORY(LogHermes)

TSet<FName> FHermesModule::CheckedModules;

void FHermesModule::StartupModule()
{
	UE_LOG(LogHermes, Log, TEXT("Loading hermes"));
	FCoreDelegates::OnAllModuleLoadingPhasesComplete.AddStatic(&FHermesModule::CheckHermesStructs, FName(EName::None));
	UE_LOG(LogHermes, Log, TEXT("Hermes loaded"));
}

void FHermesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FHermesModule::CheckHermesStructs(FName OnlyCheckModule)
{
	FModuleManager& ModuleManager = FModuleManager::Get();
	ModuleManager.OnModulesChanged().AddStatic(&FHermesModule::AfterModuleChange);
	const bool bCheckResult = FHermesStructsChecker::Check(OnlyCheckModule);
	check(bCheckResult);
}

void FHermesModule::AfterModuleChange(FName ModuleName, EModuleChangeReason ModuleChangeReason)
{
	if(ModuleChangeReason != EModuleChangeReason::ModuleLoaded || CheckedModules.Contains(ModuleName))
		return;
	
	CheckHermesStructs(ModuleName);
	CheckedModules.Add(ModuleName);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHermesModule, Hermes)