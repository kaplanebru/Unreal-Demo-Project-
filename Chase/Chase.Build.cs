using UnrealBuildTool;

public class Chase: ModuleRules
{
    public Chase(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "LevelSequence", "LevelSequence"});
    }
}