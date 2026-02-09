// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FiniteStateMachineComponent.generated.h"

class UFiniteStateMachine;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UFiniteStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UFiniteStateMachine> FSMClass;

	UPROPERTY(VisibleInstanceOnly, transient, NonTransactional)
	TObjectPtr<UFiniteStateMachine> FSMInstance;

public:	
	UFiniteStateMachineComponent();


public:
	void StartFiniteStateMachine();
	void StopFiniteStateMachine();


protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
