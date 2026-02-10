// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachineComponent.h"
#include "FiniteStateMachine.h"

UFiniteStateMachineComponent::UFiniteStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxTransitionsPerFrame = 3;
}

void UFiniteStateMachineComponent::StartFiniteStateMachine()
{
	if (IsValid(FSMClass))
	{
		FSMInstance = NewObject<UFiniteStateMachine>(this, FSMClass);
		FSMInstance->BeginPlay();
		PrimaryComponentTick.bCanEverTick = true;
	}
	else
	{
		PrimaryComponentTick.bCanEverTick = false;
	}
}

void UFiniteStateMachineComponent::StopFiniteStateMachine()
{
	if (FSMInstance)
	{
		FSMInstance->EndPlay();
	}
}

void UFiniteStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	StartFiniteStateMachine();
}

void UFiniteStateMachineComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	StopFiniteStateMachine();
}


// Called every frame
void UFiniteStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FSMInstance)
	{
		FSMInstance->Tick(DeltaTime, MaxTransitionsPerFrame);
	}
	else
	{
		PrimaryComponentTick.bCanEverTick = false;
	}
}

