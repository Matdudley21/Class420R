// Copyright Epic Games, Inc. All Rights Reserved.

#include "CitySampleModelingToolCommands.h"
#include "EditorStyleSet.h"
#include "InputCoreTypes.h"
#include "CitySampleModelingToolsStyle.h"

#define LOCTEXT_NAMESPACE "CitySampleModelingToolCommands"



FCitySampleModelingToolCommands::FCitySampleModelingToolCommands() :
	TCommands<FCitySampleModelingToolCommands>(
		"CitySampleModelingToolCommands", // Context name for fast lookup
		NSLOCTEXT("Contexts", "CitySampleModelingToolCommands", "CitySample Modeling Tools"), // Localized context name for displaying
		NAME_None, // Parent
		FCitySampleModelingToolsStyle::Get()->GetStyleSetName() // Icon Style Set
		)
{
}


void FCitySampleModelingToolCommands::RegisterCommands()
{
	UI_COMMAND(BeginISMEditorTool, "ISMEditor", "Edit ISM Components", EUserInterfaceActionType::ToggleButton, FInputChord());
}




#undef LOCTEXT_NAMESPACE
