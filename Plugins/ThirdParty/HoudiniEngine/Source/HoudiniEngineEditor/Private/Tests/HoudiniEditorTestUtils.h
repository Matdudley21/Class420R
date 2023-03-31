/*
* Copyright (c) <2018> Side Effects Software Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. The name of Side Effects Software may not be used to endorse or
*    promote products derived from this software without specific prior
*    written permission.
*
* THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
* NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#if WITH_DEV_AUTOMATION_TESTS

#include "CoreMinimal.h"

class UHoudiniAssetComponent;

class FHoudiniEditorTestUtils
{
public:
	enum EEditorScreenshotType
	{
		ENTIRE_EDITOR,
                ACTIVE_WINDOW, // Gets the active window. Probably never use this.
                DETAILS_WINDOW,
                VIEWPORT
        };

	static void InitializeTests(FAutomationTestBase* Test);
	
	static UObject* FindAssetUObject(FAutomationTestBase* Test, const FName AssetUObjectPath);

	static UHoudiniAssetComponent* InstantiateAsset(FAutomationTestBase* Test, const FName AssetUObjectPath, TFunction<void(UHoudiniAssetComponent*, const bool)> OnFinishInstantiate, const bool ErrorOnFail = true);

	static void TakeScreenshotEditor(FAutomationTestBase* Test, const FString ScreenshotName, const EEditorScreenshotType EditorScreenshotType, const FVector2D Size);

	static void TakeScreenshotViewport(FAutomationTestBase* Test, const FString ScreenshotName);
	
	static void SetUseLessCPUInTheBackground();

	static TSharedPtr<SWindow> GetMainFrameWindow();

	static TSharedPtr<SWindow> GetActiveTopLevelWindow();

	static TSharedPtr<SWindow> CreateNewDetailsWindow();

	static TSharedPtr<SWindow> CreateViewportWindow();

	static const FVector2D GDefaultEditorSize;

private:
	static void WaitForScreenshotAndCopy(FAutomationTestBase* Test, FString BaseName, TFunction<void(FAutomationTestBase*, FString)> OnScreenshotGenerated);

	static void CopyScreenshotToTestFolder(FAutomationTestBase* Test, FString BaseName);

	static FString GetTestDirectory();

	static FString GetUnrealTestDirectory();

	static FString FormatScreenshotOutputName(FString BaseName);

	static void ForceRefreshViewport();
};

#endif