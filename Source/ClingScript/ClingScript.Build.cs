﻿using System.IO;
using UnrealBuildTool;

public class ClingScript : ModuleRules
{
    public ClingScript(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.NoPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/FunctionLibrary"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/LambdaScript"));
    }
}