// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMTransition.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "LogFiniteStateMachine.h"

FFSMTransitionClass::FFSMTransitionClass()
{
}

FFSMTransitionClass::FFSMTransitionClass(FName NewName, FGuid NewCompiledNodeGuid) : FFSMElement(NewName, NewCompiledNodeGuid)
{
}

FFSMTransition::FFSMTransition()
{
}

FFSMTransition::FFSMTransition(FFSMTransitionClass& FSMTransitionClass) :
	FFSMElement(FSMTransitionClass.GetName(), FSMTransitionClass.GetCompiledNodeGuid())
{

}

void FFSMTransition::SettingConnection(UFiniteStateMachine* FiniteStateMachine, FFSMTransitionClass* FSMTransitionClass)
{
	check(FiniteStateMachine);
	check(FSMTransitionClass);


	FFSMState* FindNextNode = FiniteStateMachine->FindFSMState(FSMTransitionClass->NextNodeGUID);
	check(FindNextNode);

	NextNode = FindNextNode;
	TransitionCondition = FSMTransitionClass->TransitionCondition;
	OwningStateMachine = FiniteStateMachine;
}

bool FFSMTransition::ExecuteTransitionCondition()
{
	bool bTransitionCondition = false;
	OwningStateMachine->ProcessEvent(TransitionCondition, &bTransitionCondition);
	return bTransitionCondition;
}
