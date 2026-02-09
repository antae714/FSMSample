// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "FSMBlueprint.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FINITESTATEMACHINE_API UFSMBlueprint : public UBlueprint
{
	GENERATED_BODY()

#if WITH_EDITOR

	// Begin UBlueprintOverride
public:
	virtual void GetReparentingRules(TSet<const UClass*>& AllowedChildrenOfClasses, TSet<const UClass*>& DisallowedChildrenOfClasses) const override;
	// ~End UBlueprintOverride

#if WITH_EDITORONLY_DATA
public:
	UPROPERTY()
	TObjectPtr<UEdGraph> RootFSMGraph;
#endif	//#if WITH_EDITORONLY_DATA

#endif	//#if WITH_EDITOR
};
