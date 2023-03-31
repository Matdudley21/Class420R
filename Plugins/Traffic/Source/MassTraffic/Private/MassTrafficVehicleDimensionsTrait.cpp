// Copyright Epic Games, Inc. All Rights Reserved.

#include "MassTrafficVehicleDimensionsTrait.h"
#include "MassTrafficFragments.h"
#include "MassTrafficVehicleSimulationTrait.h"

#include "MassActorSubsystem.h"
#include "MassEntityTemplateRegistry.h"

#include "Engine/World.h"

void UMassTrafficVehicleDimensionsTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	UMassEntitySubsystem* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(&World);
	check(EntitySubsystem);

	// Add simulation config as shared fragment for length and width access.
	FMassTrafficVehicleSimulationParameters SimulationConfig;
	SimulationConfig.HalfLength = Params.HalfLength;
	SimulationConfig.HalfWidth = Params.HalfWidth;

	const uint32 SimulationConfigHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(SimulationConfig));
	const FConstSharedStruct SimulationConfigSharedFragment = EntitySubsystem->GetOrCreateConstSharedFragment<FMassTrafficVehicleSimulationParameters>(SimulationConfigHash, SimulationConfig);
	BuildContext.AddConstSharedFragment(SimulationConfigSharedFragment);
}
