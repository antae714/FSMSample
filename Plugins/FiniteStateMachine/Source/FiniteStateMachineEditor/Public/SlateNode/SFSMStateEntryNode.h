// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateNode/SFSMStateNode_Base.h"

/**
 * 
 */
class FINITESTATEMACHINEEDITOR_API SFSMStateEntryNode : public SFSMStateNode_Base
{
	SLATE_BEGIN_ARGS(SFSMStateEntryNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UFSMStateNode_Base* InNode);

	// Begin SWidget Overrides
	virtual void UpdateGraphNode() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	// ~End SWidget Overrides

protected:
	FSlateColor GetBorderBackgroundColor() const;

};
