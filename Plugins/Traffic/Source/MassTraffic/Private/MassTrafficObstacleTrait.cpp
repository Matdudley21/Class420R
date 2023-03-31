// Copyright Epic Games, Inc. All Rights Reserved.

#include "MassTrafficObstacleTrait.h"
#include "MassTrafficFragments.h"

#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassMovementFragments.h"

void UMassTrafficObstacleTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	BuildContext.AddTag<FMassTrafficObstacleTag>();
	BuildContext.AddFragment<FTransformFragment>();
	BuildContext.AddFragment<FMassVelocityFragment>();
	BuildContext.AddFragment<FAgentRadiusFragment>();
}
