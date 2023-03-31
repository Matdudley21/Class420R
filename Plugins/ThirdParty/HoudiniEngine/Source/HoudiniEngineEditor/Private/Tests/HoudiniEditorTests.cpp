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

#include "HoudiniEditorTests.h"


#if WITH_DEV_AUTOMATION_TESTS
#include "HoudiniEditorTestUtils.h"

#include "Core/Public/HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "HoudiniAssetComponent.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(HoudiniEditorEvergreenTest, "Houdini.Editor.EvergreenScreenshots", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool HoudiniEditorEvergreenTest::RunTest(const FString & Parameters)
{
	// Really force editor size
	// TODO: Move to HoudiniEditorUtils
	FHoudiniEditorTestUtils::InitializeTests(this);

	FHoudiniEditorTestUtils::InstantiateAsset(this, TEXT("/Game/TestHDAs/Evergreen"), 
        [=](UHoudiniAssetComponent * HAC, const bool IsSuccessful)
        {
                FHoudiniEditorTestUtils::TakeScreenshotEditor(this, "EverGreen_EntireEditor.png", FHoudiniEditorTestUtils::ENTIRE_EDITOR, FHoudiniEditorTestUtils::GDefaultEditorSize);
                FHoudiniEditorTestUtils::TakeScreenshotEditor(this, "EverGreen_Details.png", FHoudiniEditorTestUtils::DETAILS_WINDOW, FVector2D(400, 1130));
                FHoudiniEditorTestUtils::TakeScreenshotEditor(this, "EverGreen_EditorViewport.png", FHoudiniEditorTestUtils::VIEWPORT, FVector2D(640, 360));
                //FHoudiniEditorTestUtils::TakeScreenshotViewport(this, "EverGreen_Viewport.png"); // Viewport resolution might be inconsisent
        });
	return true;
}

#endif
