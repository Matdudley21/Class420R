// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "WorldAudioMassEntityTrait.h"

#include "MassEntitySubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "Engine/World.h"

void UWorldAudioDataMassEntityTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	UMassEntitySubsystem* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(&World);
	check(EntitySubsystem);
	
	// Add config as shared fragment
	FWorldAudioDataAudioControllerParameters AudioControllerFragment;
	AudioControllerFragment.AudioController = AudioController;
	const uint32 AudioControllerFragmentHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(AudioControllerFragment));
	const FConstSharedStruct AudioControllerSharedFragment = EntitySubsystem->GetOrCreateConstSharedFragment<FWorldAudioDataAudioControllerParameters>(AudioControllerFragmentHash, AudioControllerFragment);
	BuildContext.AddConstSharedFragment(AudioControllerSharedFragment);
}

