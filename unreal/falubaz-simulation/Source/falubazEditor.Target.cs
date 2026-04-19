using UnrealBuildTool;
using System.Collections.Generic;

public class falubazEditorTarget : TargetRules
{
	public falubazEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("falubaz");
	}
}
