#include "ChaseModule.h"
#include "Modules/ModuleManager.h"

     IMPLEMENT_MODULE(FChaseModule, Chase);

     void FChaseModule::StartupModule()
     {
         UE_LOG(LogTemp, Warning, TEXT("ChaseModule Loaded!"));
     }

     void FChaseModule::ShutdownModule()
     {
         UE_LOG(LogTemp, Warning, TEXT("ChaseModule Unloaded!"));
     }