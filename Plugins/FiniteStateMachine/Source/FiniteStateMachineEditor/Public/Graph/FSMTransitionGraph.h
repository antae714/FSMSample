// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "FSMTransitionGraph.generated.h"

class UFSMTransitionNode;

/**
 * 
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMTransitionGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UFSMTransitionNode> OwningNode;
};
