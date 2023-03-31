// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SSliceAndDicePickerWidget.h"

bool GetDataLayerName(
	const TSharedPtr<SWidget>& ParentWidget,
	UWorld* InWorld,
	FName& OutDataLayerLabelSelected);