// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MassTrafficProcessorBase.h"
#include "MassTrafficFragments.h"
#include "MassActorSubsystem.h"
#include "MassCommonFragments.h"
#include "MassTrafficFindDeviantTrafficVehiclesProcessor.generated.h"


class UMassNavigationSubsystem;

UCLASS()
class MASSTRAFFIC_API UMassTrafficFindDeviantTrafficVehiclesProcessor : public UMassTrafficProcessorBase
{
	GENERATED_BODY()

public:
	UMassTrafficFindDeviantTrafficVehiclesProcessor();

protected:
	virtual void Initialize(UObject& InOwner) override;
	virtual void ConfigureQueries() override;
	virtual void Execute(UMassEntitySubsystem& EntitySubSystem, FMassExecutionContext& Context) override;

	FMassEntityQuery NominalTrafficVehicleEntityQuery;
	
	FMassEntityQuery DeviantTrafficVehicleEntityQuery;
	
	FMassEntityQuery CorrectedTrafficVehicleEntityQuery;

	UPROPERTY(Transient)
	UMassNavigationSubsystem* NavigationSubsystem;
};
