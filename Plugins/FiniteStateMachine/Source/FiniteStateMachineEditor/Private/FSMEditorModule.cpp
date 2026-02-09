// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMEditorModule.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_FSMBlueprint.h"
#include "KismetCompilerModule.h"
#include "FSMBlueprint.h"
#include "EdGraphUtilities.h"
#include "FSMGraphFactory.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FSMEditorModule"
DECLARE_LOG_CATEGORY_EXTERN(LOG_FSMEditor, Log, All);
DEFINE_LOG_CATEGORY(LOG_FSMEditor);



void FFSMEditorModule::StartupModule()
{
	UE_LOG(LOG_FSMEditor, Log, TEXT("FFSMEditorModule::StartupModule"));

	EAssetTypeCategories::Type AssetCategoryBit = EAssetTypeCategories::None;
	//Register
	IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	//AssetCategory

	AssetCategoryBit = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("FStateMachine")), LOCTEXT("FSMCategory", "FiniteStateMachine"));
	TSharedPtr<FAssetTypeActions_FSMBlueprint> AssetTypeAction = MakeShareable(new FAssetTypeActions_FSMBlueprint(AssetCategoryBit));
	AssetToolsModule.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());

	IKismetCompilerInterface& KismetCompilerModule = FModuleManager::LoadModuleChecked<IKismetCompilerInterface>("KismetCompiler");
	KismetCompilerModule.GetCompilers().Add(&FSMBlueprintCompiler);
	
	FKismetCompilerContext::RegisterCompilerForBP(UFSMBlueprint::StaticClass(), [](UBlueprint* InBlueprint, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions)
		{
			return MakeShared<FFSMKismetCompilerContext>(CastChecked<UFSMBlueprint>(InBlueprint), InMessageLog, InCompileOptions);
		});

	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShareable(new FFSMGraphNodeFactory()));
	FEdGraphUtilities::RegisterVisualPinFactory(MakeShareable(new FFSMGraphPinFactory()));
	FEdGraphUtilities::RegisterVisualPinConnectionFactory(MakeShareable(new FFSMGraphPinConnectionFactory()));
}

void FFSMEditorModule::ShutdownModule()
{
	IKismetCompilerInterface& KismetCompilerModule = FModuleManager::LoadModuleChecked<IKismetCompilerInterface>("KismetCompiler");
	KismetCompilerModule.GetCompilers().Remove(&FSMBlueprintCompiler);
}

#undef LOCTEXT_NAMESPACE