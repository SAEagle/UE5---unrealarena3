// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

using UnrealBuildTool;

public class UnrealArena3 : ModuleRules
{
	public UnrealArena3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "PhysicsCore", "GameplayTasks", "NavigationSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { 
			"UnrealArena3/Public/Player",
			"UnrealArena3/Public/Components",
			"UnrealArena3/Public/Dev",
			"UnrealArena3/Public/Weapon",
			"UnrealArena3/Public/UI",
			"UnrealArena3/Public/Animations",
			"UnrealArena3/Public/Sound",
			"UnrealArena3/Public/Pickups",
			"UnrealArena3/Public/Weapon/Components"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
