// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MassTrafficFragments.h"

#include "MassTrafficPlayerVehicleLODProcessor.generated.h"

/*
 * Scale the LOD distance for the player vehicle so it stays around
 * way way longer that would be normally.
 */
UCLASS()
class MASSTRAFFIC_API UMassTrafficPlayerVehicleLODProcessor : public UMassLODProcessorBase
{
	GENERATED_BODY()

public:
	UMassTrafficPlayerVehicleLODProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
