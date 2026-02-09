// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMStateNode_Base.h"
#include "FSMState.h"
#include "FSMStateNode.generated.h"

/**
 *
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMStateNode : public UFSMStateNode_Base
{
	GENERATED_BODY()
public:
	// Begin UEdGraphNode Overrides
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual void PostPasteNode() override;
	virtual void PostPlacedNewNode() override;
	// ~End UEdGraphNode Overrides

	// Begin UFSMStateNode_Base Overrides
	virtual UEdGraph* GetBoundGraph() const override { return BoundGraph; }
	virtual FName GetNodeName() const override { return BoundGraph->GetFName();  }
	virtual void Compile(struct FKismetFunctionContext& Context) const override;
	// ~End UFSMStateNode_Base Overrides

	UPROPERTY()
	FFSMState State;
protected:
	UPROPERTY()
	TObjectPtr<UEdGraph> BoundGraph;
};