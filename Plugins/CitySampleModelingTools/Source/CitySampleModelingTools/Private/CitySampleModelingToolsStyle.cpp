// Copyright Epic Games, Inc. All Rights Reserved.

#include "CitySampleModelingToolsStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "EditorStyleSet.h"
#include "Interfaces/IPluginManager.h"
#include "SlateOptMacros.h"
#include "Styling/SlateStyleMacros.h"

#define IMAGE_PLUGIN_BRUSH( RelativePath, ... ) FSlateImageBrush( FCitySampleModelingToolsStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )

// This is to fix the issue that SlateStyleMacros like IMAGE_BRUSH look for RootToContentDir but StyleSet->RootToContentDir is how this style is set up
#define RootToContentDir StyleSet->RootToContentDir

FString FCitySampleModelingToolsStyle::InContent(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("CitySampleModelingTools"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FCitySampleModelingToolsStyle::StyleSet = nullptr;
TSharedPtr< class ISlateStyle > FCitySampleModelingToolsStyle::Get() { return StyleSet; }

FName FCitySampleModelingToolsStyle::GetStyleSetName()
{
	static FName ModelingToolsStyleName(TEXT("CitySampleModelingToolsStyle"));
	return ModelingToolsStyleName;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FCitySampleModelingToolsStyle::Initialize()
{
	// Const icon sizes
	const FVector2D Icon20x20(20.0f, 20.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("CitySampleModelingTools"))->GetContentDir());
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	{
		// NOTE:  Old-style, need to be replaced: 
		StyleSet->Set("CitySampleModelingToolCommands.BeginISMEditorTool", new IMAGE_PLUGIN_BRUSH("Icons/icon_ISMEditor", Icon20x20));
		StyleSet->Set("CitySampleModelingToolCommands.BeginISMEditorTool.Small", new IMAGE_PLUGIN_BRUSH("Icons/icon_ISMEditor", Icon20x20));
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
};

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef IMAGE_PLUGIN_BRUSH
#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef DEFAULT_FONT

void FCitySampleModelingToolsStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}
