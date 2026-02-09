// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FiniteStateMachine.generated.h"

struct FFSMState;
struct FFSMTransition;

UCLASS(BlueprintType, Blueprintable)
class FINITESTATEMACHINE_API UFiniteStateMachine : public UObject
{
	GENERATED_BODY()
public:
	UFiniteStateMachine();

public:
	UFUNCTION(BlueprintCallable, Category = "Finite State Machine")
	AActor* GetOwningActor() const;

	FFSMState* FindFSMState(FGuid guid);
	FFSMTransition* FindFSMTransition(FGuid guid);

public:
	void Tick(float DeltaTime);
	void BeginPlay();
	void EndPlay();

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Finite State Machine", meta = (DisplayName = "TickEvent"))
	void K2_TickEvent(float DeltaTime);

public:
	virtual UWorld* GetWorld() const override;

private:
	void UpdateState();
	void TransitionState();

public:
	/** 한프레임에 전이가능 횟수 입니다.*/
	UPROPERTY(EditAnywhere, Category = Settings)
	int32 MaxTransitionsPerFrame;

protected:
	TArray<FFSMState> States;
	TArray<FFSMTransition> Transitions;

	FFSMState* CurrrentState;
};


