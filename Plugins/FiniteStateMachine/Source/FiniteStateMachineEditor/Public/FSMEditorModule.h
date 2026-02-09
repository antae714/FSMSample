// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMBluePrintCompiler.h"
/**
 *
 */
class FFSMEditorModule : public IModuleInterface
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	FFSMBlueprintCompiler FSMBlueprintCompiler;
};
