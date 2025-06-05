#include "TeleportModule.h"
#include "Modules/ModuleManager.h"

     IMPLEMENT_MODULE(FTeleportModule, Teleport);

     void FTeleportModule::StartupModule()
     {
         UE_LOG(LogTemp, Warning, TEXT("Teleport Module Loaded!"));
     }

     void FTeleportModule::ShutdownModule()
     {
         UE_LOG(LogTemp, Warning, TEXT("Teleport Module Unloaded!"));
     }