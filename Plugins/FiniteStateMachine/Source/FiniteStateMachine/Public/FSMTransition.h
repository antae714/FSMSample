// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.h"
#include "FSMTransition.generated.h"

struct FFSMTransitionClass;
class UFiniteStateMachine;

USTRUCT()
struct FINITESTATEMACHINE_API FFSMTransitionClass : public FFSMElement
{
	GENERATED_BODY()
public:
	FFSMTransitionClass();
	FFSMTransitionClass(FName NewName, FGuid NewCompiledNodeGuid);


public:
	UPROPERTY()
	TObjectPtr<UFunction> TransitionCondition;

	UPROPERTY()
	FGuid NextNodeGUID;
};


/**
 * 
 */
USTRUCT()
struct FINITESTATEMACHINE_API FFSMTransition : public FFSMElement
{
	GENERATED_BODY()
public:
	FFSMTransition();
	FFSMTransition(FFSMTransitionClass& FSMTransitionClass);

public:
	void SettingConnection(UFiniteStateMachine* FiniteStateMachine, FFSMTransitionClass* FSMTransitionClass);
	bool ExecuteTransitionCondition();

public:
	struct FFSMState* NextNode;

protected:
	TObjectPtr<UFunction> TransitionCondition;

protected:
	TObjectPtr<UFiniteStateMachine> OwningStateMachine;
};

