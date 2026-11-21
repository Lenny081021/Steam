using UnrealBuildTool;

public class RealLifeSurvival : ModuleRules
{
    public RealLifeSurvival(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG",
            "Slate", "SlateCore", "NavigationSystem", "AIModule", "GameplayTasks",
            "PhysicsCore", "Chaos", "ChaosVehicles", "Niagara", "OnlineSubsystem"
        });
    }
}
