// Copyright Epic Games, Inc. All Rights Reserved.

#include "MassTrafficInitIntersectionsProcessor.h"
#include "MassTrafficFragments.h"
#include "MassTrafficDelegates.h"
#include "MassTrafficFieldOperations.h"
#include "MassCrowdSubsystem.h"


UMassTrafficInitIntersectionsProcessor::UMassTrafficInitIntersectionsProcessor()
{
	bAutoRegisterWithProcessingPhases = false;
}

void UMassTrafficInitIntersectionsProcessor::ConfigureQueries() 
{
	EntityQuery.AddRequirement<FMassTrafficIntersectionFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
}

void UMassTrafficInitIntersectionsProcessor::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	// Cast AuxData to required FMassTrafficIntersectionsSpawnData
	const FInstancedStruct& AuxInput = Context.GetMutableAuxData();
	if (!ensure(AuxInput.GetPtr<FMassTrafficIntersectionsSpawnData>()))
	{
		return;
	}
	FMassTrafficIntersectionsSpawnData& IntersectionsSpawnData = AuxInput.GetMutable<FMassTrafficIntersectionsSpawnData>();

	
	// Get world
	const UWorld* World = GetWorld();

	// Get Mass crowd subsystem.
	UMassCrowdSubsystem* MassCrowdSubsystem = UWorld::GetSubsystem<UMassCrowdSubsystem>(World);

	// Process chunks
	int32 Offset = 0;
	EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, [&](FMassExecutionContext& QueryContext)
	{
		const int32 NumEntities = QueryContext.GetNumEntities();
		const TArrayView<FMassTrafficIntersectionFragment> TrafficIntersectionFragments = QueryContext.GetMutableFragmentView<FMassTrafficIntersectionFragment>();
		const TArrayView<FTransformFragment> TransformFragments = QueryContext.GetMutableFragmentView<FTransformFragment>();

		// Swap in pre-initialized fragments
		// Note: We do a Memswap here instead of a Memcpy as Memcpy would copy the internal TArray 
		// data pointers from the AuxInput TArrays which will be freed at the end of spawn
		FMemory::Memswap(TrafficIntersectionFragments.GetData(), &IntersectionsSpawnData.IntersectionFragments[Offset], sizeof(FMassTrafficIntersectionFragment) * NumEntities);

		// Swap in transforms
		check(sizeof(FTransformFragment) == sizeof(FTransform));
		FMemory::Memswap(TransformFragments.GetData(), &IntersectionsSpawnData.IntersectionTransforms[Offset], sizeof(FTransformFragment) * NumEntities);

		// Init intersection lane states -
		for (int32 Index = 0; Index < NumEntities; ++Index)
		{
			FMassTrafficIntersectionFragment& TrafficIntersectionFragment = TrafficIntersectionFragments[Index];

			// Close all vehicle and pedestrian lanes, and stop all traffic lights, controlled by this intersection.
			// The 'update intersection processor' will take it from here.
			TrafficIntersectionFragment.RestartIntersection(MassCrowdSubsystem);

			// Cache intersection entities in the traffic coordinator
			MassTrafficSubsystem->RegisterTrafficIntersectionEntity(TrafficIntersectionFragment.ZoneIndex, QueryContext.GetEntity(Index));
		}

		Offset += NumEntities;
	});
	
	// Broadcast intersections initialized
	UE::MassTrafficDelegates::OnPostInitTrafficIntersections.Broadcast(MassTrafficSubsystem.Get());

	check(MassTrafficSubsystem.IsValid());
	MassTrafficSubsystem->PerformFieldOperation(UMassTrafficRetimeIntersectionPeriodsFieldOperation::StaticClass());
}
