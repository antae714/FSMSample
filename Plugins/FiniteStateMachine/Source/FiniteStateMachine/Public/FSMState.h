// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.h"
#include "FSMState.generated.h"


struct FFSMStateClass;
struct FFSMTransition;
class UFiniteStateMachine;

/**
 * BPClass 에서 사용할 상태정보입니다.
 */
USTRUCT()
struct FINITESTATEMACHINE_API FFSMStateClass : public FFSMElement
{
	GENERATED_BODY()

public:
	FFSMStateClass();
	FFSMStateClass(FName NewName, FGuid NewCompiledNodeGuid);

public:
	UPROPERTY()
	TObjectPtr<UFunction> StateEntry;

	UPROPERTY()
	TObjectPtr<UFunction> StateUpdate;
	
	UPROPERTY()
	TObjectPtr<UFunction> StateExit;

	UPROPERTY()
	TArray<FGuid> ConnectedTransitionGUID;
};

/**
 * 실제 상태입니다.
 */
USTRUCT()
struct FINITESTATEMACHINE_API FFSMState : public FFSMElement
{
	GENERATED_BODY()

public:
	FFSMState();
	FFSMState(FFSMStateClass& FSMStateClass);

public:
	void SettingConnection(UFiniteStateMachine* FiniteStateMachine, FFSMStateClass* FSMStateClass);
	void ExecuteStateEntry();
	void ExecuteStateUpdate();
	void ExecuteStateExit();

public:
	TArray<FFSMTransition*> ConnectedTransitions;

protected:
	UPROPERTY()
	TObjectPtr<UFunction> StateEntry;

	UPROPERTY()
	TObjectPtr<UFunction> StateUpdate;
	
	UPROPERTY()
	TObjectPtr<UFunction> StateExit;

	/** 소유중인 상태머신 입니다. */
	UPROPERTY()
	TObjectPtr<UFiniteStateMachine> OwningStateMachine;
};