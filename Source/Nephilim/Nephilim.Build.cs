// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Nephilim : ModuleRules
{
	public Nephilim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "StateTreeModule", "StateTreeModule", "ArcECS"});
        PrivateDependencyModuleNames.AddRange(new string[] { "ArcECS", "UMG", "NetCore" });
	}
}
