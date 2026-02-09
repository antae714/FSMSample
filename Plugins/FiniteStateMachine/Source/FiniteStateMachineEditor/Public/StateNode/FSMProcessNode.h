// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "FSMProcessNode.generated.h"

/**
 *
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMProcessNode : public UK2Node
{
	GENERATED_BODY()
public:

	// Begin UEdGraphNode Overrides
	virtual void AllocateDefaultPins() override;
	virtual bool CanUserDeleteNode() const override { return false; }
	virtual bool IsNodeRootSet() const override { return true; }
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void EarlyValidation(FCompilerResultsLog& MessageLog) const;
	virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;
	// ~End UEdGraphNode Overrides

	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;
};