// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMBlueprintGeneratedClass.generated.h"


struct FFSMStateClass;
struct FFSMTransitionClass;


/**
 * 
 */
UCLASS()
class FINITESTATEMACHINE_API UFSMBlueprintGeneratedClass : public UBlueprintGeneratedClass
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FFSMStateClass> States;

	UPROPERTY()
	TArray<FFSMTransitionClass> Transitions;

	UPROPERTY()
	FGuid EnteryStateGUID;
};
