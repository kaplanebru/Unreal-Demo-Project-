#include "TorsoModule.h"
#include "Modules/ModuleManager.h"

     IMPLEMENT_MODULE(FTorsoModule, Torso);

     void FTorsoModule::StartupModule()
     {
         UE_LOG(LogTemp, Warning, TEXT("TorsoModule Loaded!"));
     }

     void FTorsoModule::ShutdownModule()
     {
         UE_LOG(LogTemp, Warning, TEXT("TorsoModule Unloaded!"));
     }