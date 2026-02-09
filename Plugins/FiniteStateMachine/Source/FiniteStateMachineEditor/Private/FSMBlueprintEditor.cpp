// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMBlueprintEditor.h"
#include "FSMBlueprint.h"
#include "SMyBlueprint.h"

void FFSMBlueprintEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UFSMBlueprint* InObject)
{
	InitBlueprintEditor(Mode, InitToolkitHost, { InObject }, false);
}
