// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameFarmManager : ModuleRules
{
	public GameFarmManager(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GameFarmManager",
			"GameFarmManager/Core",
			"GameFarmManager/Variant_Horror",
			"GameFarmManager/Variant_Horror/UI",
			"GameFarmManager/Variant_Shooter",
			"GameFarmManager/Variant_Shooter/AI",
			"GameFarmManager/Variant_Shooter/UI",
			"GameFarmManager/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
