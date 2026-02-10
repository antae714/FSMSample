// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMBlueprintGeneratedClass.h"
#include "LogFiniteStateMachine.h"

UFiniteStateMachine::UFiniteStateMachine()
{
}

AActor* UFiniteStateMachine::GetOwningActor() const
{
	UObject* Outer = GetOuter();
	while (Outer)
	{
		AActor* Actor = Cast<AActor>(Outer);
		if (Actor)
		{
			return Actor;
		}
		Outer = Outer->GetOuter();
	}
	return nullptr;
}

FFSMState* UFiniteStateMachine::FindFSMState(FGuid guid)
{
	return  States.FindByKey(guid);
}

FFSMTransition* UFiniteStateMachine::FindFSMTransition(FGuid guid)
{
	return Transitions.FindByKey(guid);
}

void UFiniteStateMachine::Tick(float DeltaTime, int32 MaxTransitionsPerFrame)
{
	K2_TickEvent(DeltaTime);

	if (!CurrrentState)
	{
		return;
	}

	int count = 0;
	FFSMState* TempState = nullptr;
	while (TempState != CurrrentState && count++ < MaxTransitionsPerFrame)
	{
		TempState = CurrrentState;
		UpdateState();
		TransitionState();
	}
}

void UFiniteStateMachine::BeginPlay()
{
	UFSMBlueprintGeneratedClass* FSMclass = Cast<UFSMBlueprintGeneratedClass>(GetClass());

	States.Empty(FSMclass->States.Num());
	Transitions.Empty(FSMclass->Transitions.Num());

	for (auto& FFSMStateClass : FSMclass->States)
	{
		States.Emplace(FFSMStateClass);
	}
	for (auto& FSMTransitionClass : FSMclass->Transitions)
	{
		Transitions.Emplace(FSMTransitionClass);
	}

	for (int i = 0; i < States.Num(); i++)
	{
		States[i].SettingConnection(this, &FSMclass->States[i]);
	}
	for (int i = 0; i < Transitions.Num(); i++)
	{
		Transitions[i].SettingConnection(this, &FSMclass->Transitions[i]);
	}

	CurrrentState = States.FindByKey(FSMclass->EnteryStateGUID);
	if (CurrrentState)
	{
		CurrrentState->ExecuteStateEntry();
	}
	else
	{
		UE_LOG(LogFiniteStateMachine, Warning, TEXT("EnteryState Is Not Found"));
		return;
	}
}

void UFiniteStateMachine::EndPlay()
{
	if (CurrrentState)
	{
		CurrrentState->ExecuteStateExit();
		CurrrentState = nullptr;
	}

	States.Empty();
	Transitions.Empty();
}

void UFiniteStateMachine::UpdateState()
{
	CurrrentState->ExecuteStateUpdate();
}

void UFiniteStateMachine::TransitionState()
{
	for (auto& item : CurrrentState->ConnectedTransitions)
	{
		if (item->ExecuteTransitionCondition())
		{
			CurrrentState->ExecuteStateExit();
			CurrrentState = item->NextNode;
			CurrrentState->ExecuteStateEntry();
		}
	}
}

UWorld* UFiniteStateMachine::GetWorld() const
{
	if (HasAllFlags(RF_ClassDefaultObject))
	{
		// If we are a CDO, we must return nullptr instead of calling Outer->GetWorld() to fool UObject::ImplementsGetWorld.
		return nullptr;
	}

	return Super::GetWorld();
}
