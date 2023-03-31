// Copyright Epic Games, Inc. All Rights Reserved.

#include "MassTrafficIntersectionSimulationTrait.h"
#include "MassTrafficFragments.h"

#include "MassEntityTemplateRegistry.h"
#include "MassCommonFragments.h"

void UMassTrafficIntersectionSimulationTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	BuildContext.AddTag<FMassTrafficIntersectionTag>();
	BuildContext.AddFragment<FMassTrafficIntersectionFragment>();
	BuildContext.AddFragment<FTransformFragment>();
}
