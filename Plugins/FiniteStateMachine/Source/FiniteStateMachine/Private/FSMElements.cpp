// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMElements.h"

FFSMElement::FFSMElement()
{
}

FFSMElement::FFSMElement(FName name, FGuid compiledNodeGuid)
{
	Name = name;
	CompiledNodeGuid = compiledNodeGuid;
}

bool FFSMElement::operator==(FGuid nodeGuid)
{
	return CompiledNodeGuid == nodeGuid;
}
