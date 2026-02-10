// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"
#include "FSMGraph.generated.h"


class UFSMStateEntryNode;
class UFSMProcessNode;

/**
 * 
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UFSMStateEntryNode> EntryNode;
};
