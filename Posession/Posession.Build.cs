using UnrealBuildTool;

public class Posession : ModuleRules
{
    public Posession(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Marcus_Mansion" }); //marcus mansion is added temporaryly




        //PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
       // PublicDependencyModuleNames.AddRange(new string[] { "Core" });
        //PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Slate", "SlateCore" });

        // Enable hot-reloading
        // bUseUnity = false;
    }
}