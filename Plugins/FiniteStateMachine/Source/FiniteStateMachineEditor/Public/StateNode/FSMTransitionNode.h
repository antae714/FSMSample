// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMStateNode_Base.h"
#include "FSMTransitionNode.generated.h"

/**
 *
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMTransitionNode : public UFSMStateNode_Base
{
	GENERATED_BODY()

public:
	UFSMTransitionNode(const FObjectInitializer& ObjectInitializer);

public:
	// Begin UEdGraphNode Overrides
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PostPlacedNewNode() override;
	virtual void PostPasteNode() override;
	// ~End UEdGraphNode Overrides
	
	// Begin UFSMStateNode_Base Overrides
	virtual UEdGraph* GetBoundGraph() const override { return BoundGraph; }
	virtual void Compile(struct FKismetFunctionContext& Context) const override;
	// ~End UFSMStateNode_Base Overrides


	UFSMStateNode_Base* GetPrevState() const;
	UFSMStateNode_Base* GetNextState() const;
	void CreateConnections(UFSMStateNode_Base* PreviousState, UFSMStateNode_Base* NextState);

protected:
	UPROPERTY()
	TObjectPtr<UEdGraph> BoundGraph;
};	
