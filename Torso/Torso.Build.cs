using UnrealBuildTool;

public class Torso: ModuleRules
{
    public Torso(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Marcus_Mansion"});
    }
}