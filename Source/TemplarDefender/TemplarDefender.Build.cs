// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TemplarDefender : ModuleRules
{
	public TemplarDefender(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "UMG", "Slate", "SlateCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate" , "SlateCore"});
	}
}
