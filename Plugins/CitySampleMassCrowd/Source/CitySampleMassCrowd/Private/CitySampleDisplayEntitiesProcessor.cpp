// Copyright Epic Games, Inc. All Rights Reserved.

#include "CitySampleDisplayEntitiesProcessor.h"
#include "MassRepresentationSubsystem.h"
#include "MassCommonFragments.h"
#include "MassRepresentationTypes.h"
#include "MassLODSubsystem.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

namespace CitySample
{
	int32 GDisplayEntities = 0;
	FAutoConsoleVariableRef CVarCitySampleDisplayEntities(TEXT("CitySample.DisplayEntities"), GDisplayEntities, TEXT("Display all Mass entities that are being updated"));

	float GDisplayEntitiesFarClippingDistance = 300000.0f; // 3km
	FAutoConsoleVariableRef CVarCitySampleDisplayEntitiesFarClippingDistance(TEXT("CitySample.DisplayEntitiesFarClippingDistance"), GDisplayEntitiesFarClippingDistance, TEXT("Far clipping distance when displaying frosty entities"));

	float GDisplayEntitiesFOVAngleInDegrees = 50.0f; // degrees
	FAutoConsoleVariableRef CVarCitySampleFOVAngleInDegrees(TEXT("CitySample.DisplayEntitiesFOVAngleInDegrees"), GDisplayEntitiesFOVAngleInDegrees, TEXT("FOV half angle in degrees to cull entities"));
}

namespace UE::MassCrowd
{
	extern MASSCROWD_API int32 GCrowdTurnOffVisualization;
}

namespace UE::MassTraffic
{
	extern MASSTRAFFIC_API int32 GTrafficTurnOffVisualization;
}

void UCitySampleDisplayEntitiesProcessor::Initialize(UObject& Owner)
{
	Super::Initialize(Owner);
	this->ProcessingPhase = EMassProcessingPhase::EndPhysics;

	RepresentationSubsystem = UWorld::GetSubsystem<UMassRepresentationSubsystem>(Owner.GetWorld());
	LODSubsystem = UWorld::GetSubsystem<UMassLODSubsystem>(Owner.GetWorld());
	check(RepresentationSubsystem);
	for (FCitySampleDisplayEntitiesConfig& Config : DisplayConfigs)
	{
		Config.StaticMeshDescIndex = RepresentationSubsystem->FindOrAddStaticMeshDesc(Config.StaticMeshInstanceDesc);
	}
}

void UCitySampleDisplayEntitiesProcessor::ConfigureQueries()
{
	for (FCitySampleDisplayEntitiesConfig& Config : DisplayConfigs)
	{
		Config.EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
		if(Config.TagFilter.GetScriptStruct())
		{
			Config.EntityQuery.AddTagRequirement(*Config.TagFilter.GetScriptStruct(),EMassFragmentPresence::All);
		}
	}
}

void UCitySampleDisplayEntitiesProcessor::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	UE::MassTraffic::GTrafficTurnOffVisualization = UE::MassCrowd::GCrowdTurnOffVisualization = CitySample::GDisplayEntities;
	if (!CitySample::GDisplayEntities)
	{
		return;
	}

	check(LODSubsystem);
	FVector LocalViewerLocation;
	FVector LocalViewerDirection;
	const float CosFOVAngleToDriveVisibility = FMath::Cos(FMath::DegreesToRadians(CitySample::GDisplayEntitiesFOVAngleInDegrees));
	const float MaxRenderDistSquared = FMath::Square(CitySample::GDisplayEntitiesFarClippingDistance);
	const TArray<FViewerInfo>& Viewers = LODSubsystem->GetViewers();
	for (const FViewerInfo& Viewer : Viewers)
	{
		if (Viewer.PlayerController && Viewer.PlayerController->IsLocalController())
		{
			FVector PlayerCameraLocation(ForceInitToZero);
			FRotator PlayerCameraRotation(FRotator::ZeroRotator);
			Viewer.PlayerController->GetPlayerViewPoint(PlayerCameraLocation, PlayerCameraRotation);
			LocalViewerLocation = PlayerCameraLocation;
			LocalViewerDirection = PlayerCameraRotation.Vector();
			break;
		}
	}

	check(RepresentationSubsystem);
	FMassInstancedStaticMeshInfoArrayView ISMInfo = RepresentationSubsystem->GetMutableInstancedStaticMeshInfos();

	for (FCitySampleDisplayEntitiesConfig& Config : DisplayConfigs)
	{
		Config.EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, [&Config, &ISMInfo, &LocalViewerLocation, &LocalViewerDirection, &CosFOVAngleToDriveVisibility, &MaxRenderDistSquared](FMassExecutionContext& Context)
		{
			TConstArrayView<FTransformFragment> TransformList = Context.GetFragmentView<FTransformFragment>();

			const int32 NumEntities = Context.GetNumEntities();
			for (int32 EntityIdx = 0; EntityIdx < NumEntities; EntityIdx++)
			{
				const FTransformFragment& TransformFragment = TransformList[EntityIdx];
				const FVector ViewerToEntity = TransformFragment.GetTransform().GetLocation() - LocalViewerLocation;
				const float DistToViewerSquared = ViewerToEntity.SizeSquared();
				if (DistToViewerSquared > MaxRenderDistSquared)
				{
					continue;
				}

				const FVector ViewerToEntityNorm = ViewerToEntity * FMath::InvSqrt(DistToViewerSquared);
				const float Dot = LocalViewerDirection | ViewerToEntityNorm;

				// Skip entities not in frustum
				if (Dot < CosFOVAngleToDriveVisibility)
				{
					continue;
				}

				if (ISMInfo[Config.StaticMeshDescIndex].ShouldUseTransformOffset())
				{
					const FTransform& TransformOffset = ISMInfo[Config.StaticMeshDescIndex].GetTransformOffset();
					const FTransform SMTransform = TransformOffset * TransformFragment.GetTransform();

					ISMInfo[Config.StaticMeshDescIndex].AddBatchedTransform(GetTypeHash(Context.GetEntity(EntityIdx)), SMTransform, SMTransform, 0.0f);
				}
				else
				{
					ISMInfo[Config.StaticMeshDescIndex].AddBatchedTransform(GetTypeHash(Context.GetEntity(EntityIdx)), TransformFragment.GetTransform(), TransformFragment.GetTransform(), 0.0f);
				}
			}
		});
	}
}
