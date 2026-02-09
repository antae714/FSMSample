// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "FSMStateGraph.generated.h"

class UFSMStateNode;


/**
 * 
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMStateGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UFSMStateNode> OwningNode;
};
