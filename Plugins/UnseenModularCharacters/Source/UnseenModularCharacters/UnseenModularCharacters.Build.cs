using UnrealBuildTool;

public class UnseenModularCharacters : ModuleRules
{
	public UnseenModularCharacters(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		// Put modules containing "FPaths", "FFileHelper", etc. in the dependencies so they're available for runtime builds
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",      // Needed if you're referencing engine-level path helpers
			"Json",
			"JsonUtilities"
		});

		// Modules needed internally but not exposed as part of your plugin’s public interface
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			//  ... add others here if needed (e.g., 'InputCore', 'RHI', etc.)
		});

		// If you have specific includes that you only need in the editor, keep them out of runtime builds, or create an Editor module
		// DynamicallyLoadedModuleNames.AddRange(...);
	}
}