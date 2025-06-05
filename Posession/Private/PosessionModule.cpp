#include "PosessionModule.h"
#include "Modules/ModuleManager.h"

     IMPLEMENT_MODULE(FPosessionModule, Posession);

     //     IMPLEMENT_MODULE(FDefaultModuleImpl, Posession);

     void FPosessionModule::StartupModule()
     {
         UE_LOG(LogTemp, Warning, TEXT("Posession Module Loaded!"));
     }

     void FPosessionModule::ShutdownModule()
     {
         UE_LOG(LogTemp, Warning, TEXT("Posession Module Unloaded!"));
     }