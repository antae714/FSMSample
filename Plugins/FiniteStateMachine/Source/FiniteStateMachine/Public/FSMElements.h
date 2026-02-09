// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.generated.h"



/**
 * 
 */
USTRUCT()
struct FINITESTATEMACHINE_API FFSMElement
{
	GENERATED_BODY()
public:
	FFSMElement();
	FFSMElement(FName name, FGuid compiledNodeGuid);

public:
	FName GetName() { return Name; }
	FGuid GetCompiledNodeGuid() { return CompiledNodeGuid; }

public:
	bool operator==(FGuid nodeGuid);

protected:
	UPROPERTY()
	FName Name;

	UPROPERTY()
	FGuid CompiledNodeGuid;
};
