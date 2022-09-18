// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealArena3Target : TargetRules
{
	public UnrealArena3Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "UnrealArena3" } );
	}
}
