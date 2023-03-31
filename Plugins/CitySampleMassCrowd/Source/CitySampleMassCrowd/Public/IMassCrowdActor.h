// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "MassCommonTypes.h"
#include "UObject/Interface.h"

#include "IMassCrowdActor.generated.h"

class UMassEntitySubsystem;

UINTERFACE(Blueprintable)
class CITYSAMPLEMASSCROWD_API UMassCrowdActorInterface : public UInterface
{
    GENERATED_BODY()
};

class IMassCrowdActorInterface
{
	GENERATED_BODY()
	
public:

	virtual void OnGetOrSpawn(UMassEntitySubsystem* EntitySubsystem, const FMassEntityHandle MassAgent) = 0;

	virtual void SetAdditionalMeshOffset(const float Offset) = 0;
};