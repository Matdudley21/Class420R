// Copyright Epic Games, Inc. All Rights Reserved.

#include "CitySampleModelingToolsModule.h"
#include "Features/IModularFeatures.h"
#include "CitySampleModelingToolsStyle.h"
#include "CitySampleModelingToolCommands.h"

#include "ISMEditorTool.h"

#define LOCTEXT_NAMESPACE "FCitySampleModelingToolsModule"

void FCitySampleModelingToolsModule::StartupModule()
{
	FCitySampleModelingToolsStyle::Initialize();
	FCitySampleModelingToolCommands::Register();

	IModularFeatures::Get().RegisterModularFeature(IModelingModeToolExtension::GetModularFeatureName(), this);
}

void FCitySampleModelingToolsModule::ShutdownModule()
{
	IModularFeatures::Get().UnregisterModularFeature(IModelingModeToolExtension::GetModularFeatureName(), this);

	FCitySampleModelingToolCommands::Unregister();
	FCitySampleModelingToolsStyle::Shutdown();
}




FText FCitySampleModelingToolsModule::GetExtensionName()
{
	return LOCTEXT("ExtensionName", "CitySampleTools");
}

FText FCitySampleModelingToolsModule::GetToolSectionName()
{
	return LOCTEXT("SectionName", "CitySample Tools");
}

void FCitySampleModelingToolsModule::GetExtensionTools(const FExtensionToolQueryInfo& QueryInfo, TArray<FExtensionToolDescription>& ToolsOut)
{
	//QueryInfo.bIsInfoQueryOnly
	FExtensionToolDescription ISMEditorToolInfo;
	ISMEditorToolInfo.ToolName = LOCTEXT("ISMEditorToolName", "ISM Editor");
	ISMEditorToolInfo.ToolCommand = FCitySampleModelingToolCommands::Get().BeginISMEditorTool;
	ISMEditorToolInfo.ToolBuilder = NewObject<UISMEditorToolBuilder>();

	ToolsOut.Add(ISMEditorToolInfo);
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCitySampleModelingToolsModule, CitySampleModelingTools)
