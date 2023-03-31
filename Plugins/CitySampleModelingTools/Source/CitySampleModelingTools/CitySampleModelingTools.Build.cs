// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CitySampleModelingTools : ModuleRules
{
	public CitySampleModelingTools(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		PublicIncludePathModuleNames.AddRange(
			new string[] {
				"AnimationCore",			// For the BoneWeights.h include
			}
		);
	
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Eigen",
                "InteractiveToolsFramework",
				"GeometryCore",
				"GeometryFramework",
				"GeometryAlgorithms",
				"DynamicMesh",
				"MeshConversion",
				"MeshDescription",
                "StaticMeshDescription",
                "SkeletalMeshDescription",
				"ModelingComponents",
				"ModelingOperators",
				"ModelingToolsEditorMode"
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"ApplicationCore",
				"Slate",
				"SlateCore",
				"Engine",
				"InputCore",
				"EditorFramework",
				"UnrealEd",
				"ContentBrowser",
				"LevelEditor",
				"StatusBar",
				"EditorStyle",
				"Projects",
				"EditorInteractiveToolsFramework",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
