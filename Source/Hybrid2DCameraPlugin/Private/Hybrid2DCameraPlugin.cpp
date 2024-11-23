#include "Hybrid2DCameraPlugin.h"

#define LOCTEXT_NAMESPACE "FHybrid2DCameraPluginModule"

void FHybrid2DCameraPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FHybrid2DCameraPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHybrid2DCameraPluginModule, Hybrid2DCameraPlugin)