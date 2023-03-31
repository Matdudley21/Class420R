// Copyright Epic Games, Inc. All Rights Reserved.

#include "MassTrafficConstrainedTrailerTrait.h"
#include "MassTrafficFragments.h"

#include "MassEntityTemplateRegistry.h"
#include "MassSimulationLOD.h"
#include "MassTrafficSubsystem.h"

void UMassTrafficConstrainedTrailerTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	UMassEntitySubsystem* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(&World);
	UMassTrafficSubsystem* MassTrafficSubsystem = UWorld::GetSubsystem<UMassTrafficSubsystem>(&World);
	check(EntitySubsystem);
	check(MassTrafficSubsystem);

	// Add Params as shared fragment
	const uint32 ParamsHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(Params));
	const FConstSharedStruct ParamsSharedFragment = EntitySubsystem->GetOrCreateConstSharedFragment<FMassTrafficConstrainedTrailerParameters>(ParamsHash, Params);
	BuildContext.AddConstSharedFragment(ParamsSharedFragment);

	// Constrained trailer ref fragment
	BuildContext.AddFragment<FMassTrafficConstrainedTrailerFragment>();

	IF_MASSTRAFFIC_ENABLE_DEBUG(BuildContext.AddFragment<FMassTrafficDebugFragment>());
}
