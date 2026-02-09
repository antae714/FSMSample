// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "FSMTransition.h"

#include "LogFiniteStateMachine.h"

FFSMStateClass::FFSMStateClass()
{
}

FFSMStateClass::FFSMStateClass(FName NewName, FGuid NewCompiledNodeGuid) : FFSMElement(NewName, NewCompiledNodeGuid)
{
}

FFSMState::FFSMState()
{
}

FFSMState::FFSMState(FFSMStateClass& FSMStateClass) : FFSMElement(FSMStateClass.GetName(), FSMStateClass.GetCompiledNodeGuid())
{
}

void FFSMState::SettingConnection(UFiniteStateMachine* FiniteStateMachine, FFSMStateClass* FSMStateClass)
{
	check(FiniteStateMachine);
	check(FSMStateClass);

	for (auto& item : FSMStateClass->ConnectedTransitionGUID)
	{
		FFSMTransition* ConectedTransition = FiniteStateMachine->FindFSMTransition(item);
		check(ConectedTransition);

		ConnectedTransitions.Add(ConectedTransition);
	}

	StateEntry = FSMStateClass->StateEntry;
	StateUpdate = FSMStateClass->StateUpdate;
	StateExit = FSMStateClass->StateExit;

	OwningStateMachine = FiniteStateMachine;
}


void FFSMState::ExecuteStateEntry()
{
	if (StateEntry)
	{
		OwningStateMachine->ProcessEvent(StateEntry, nullptr);
	}
}

void FFSMState::ExecuteStateUpdate()
{
	if (StateUpdate)
	{
		OwningStateMachine->ProcessEvent(StateUpdate, nullptr);
	}
}

void FFSMState::ExecuteStateExit()
{
	if (StateExit)
	{
		OwningStateMachine->ProcessEvent(StateExit, nullptr);
	}
}
