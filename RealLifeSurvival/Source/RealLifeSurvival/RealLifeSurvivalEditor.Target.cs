using UnrealBuildTool;
using System.Collections.Generic;

public class RealLifeSurvivalEditorTarget : TargetRules
{
    public RealLifeSurvivalEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("RealLifeSurvival");
    }
}
