// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSliceAndDiceDataLayerPicker.h"
	
#include "WorldPartition/DataLayer/WorldDataLayers.h"
#include "WorldPartition/DataLayer/DataLayer.h"

#define LOCTEXT_NAMESPACE "SliceAndDiceDataLayerPicker"

bool GetDataLayerName(
	const TSharedPtr<SWidget>& ParentWidget,
	UWorld* InWorld,
	FName& OutDataLayerSelected)
{
	TArray<FName> DataLayerLabels;
	if (InWorld)
	{
		if (AWorldDataLayers* WorldDataLayers = InWorld->GetWorldDataLayers())
		{
			WorldDataLayers->ForEachDataLayer([&DataLayerLabels](class UDataLayer* DataLayer) {
				DataLayerLabels.Emplace(DataLayer->GetDataLayerLabel());
				return true;
			});
		}
	}

	DataLayerLabels.Sort(FNameLexicalLess());

	return SliceAndDicePickerWidget::PickFromList(
		ParentWidget,
		LOCTEXT("Title", "Select Data Layer"),
		LOCTEXT("Label", "Select which data layer to delete from:"),
		DataLayerLabels,
		OutDataLayerSelected);
}

#undef LOCTEXT_NAMESPACE