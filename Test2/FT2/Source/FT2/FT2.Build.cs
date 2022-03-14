// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FT2 : ModuleRules
{
	public FT2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
