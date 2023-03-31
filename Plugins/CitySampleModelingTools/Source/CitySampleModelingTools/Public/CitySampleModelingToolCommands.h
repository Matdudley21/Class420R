// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"


/**
 * TInteractiveToolCommands implementation for this module that provides standard Editor hotkey support
 */
class CITYSAMPLEMODELINGTOOLS_API FCitySampleModelingToolCommands : public TCommands<FCitySampleModelingToolCommands>
{
public:
	FCitySampleModelingToolCommands();

	TSharedPtr<FUICommandInfo> BeginISMEditorTool;

	/**
	 * Initialize commands
	 */
	virtual void RegisterCommands() override;
};
