// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMBluePrintCompiler.h"
#include "FSMBlueprint.h"
#include "FiniteStateMachine.h"
#include "FSMBlueprintGeneratedClass.h"
#include "Kismet2/KismetReinstanceUtilities.h"
#include "Graph/FSMGraphSchema.h"
#include "EdGraphUtilities.h"

#include "StateNode/FSMStateNode_Base.h"
#include "StateNode/FSMStateNode.h"
#include "StateNode/FSMTransitionNode.h"
#include "StateNode/FSMStateEntryNode.h"
#include "StateNode/FSMTransitionResultNode.h"




bool FFSMBlueprintCompiler::CanCompile(const UBlueprint* Blueprint)
{
	return Cast<UFSMBlueprint>(Blueprint) != nullptr;
}

void FFSMBlueprintCompiler::Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results)
{
	if (UFSMBlueprint* fsmBlueprint = CastChecked<UFSMBlueprint>(Blueprint))
	{
		FKismetCompilerContext Compiler(Blueprint, Results, CompileOptions);
		Compiler.Compile();
		check(Compiler.NewClass);
		//FWidgetBlueprintCompilerContext Compiler(UFSMBlueprint, Results, CompileOptions);
		//Compiler.Compile();
		//check(Compiler.NewClass);
	}
}

bool FFSMBlueprintCompiler::GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const
{
	if (ParentClass == UFiniteStateMachine::StaticClass() || ParentClass->IsChildOf(UFiniteStateMachine::StaticClass()))
	{
		OutBlueprintClass = UFSMBlueprint::StaticClass();
		OutBlueprintGeneratedClass = UFSMBlueprintGeneratedClass::StaticClass();
		return true;
	}

	return false;
}

FFSMKismetCompilerContext::FFSMKismetCompilerContext(UFSMBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions)
	: FKismetCompilerContext(SourceSketch, InMessageLog, InCompileOptions)
{
}

void FFSMKismetCompilerContext::SpawnNewClass(const FString& NewClassName)
{
	NewClass = FindObject<UFSMBlueprintGeneratedClass>(Blueprint->GetOutermost(), *NewClassName);

	if (NewClass == NULL)
	{
		NewClass = NewObject<UFSMBlueprintGeneratedClass>(Blueprint->GetOutermost(), *NewClassName, RF_Public | RF_Transactional);
	}
	else
	{
		// Already existed, but wasn't linked in the Blueprint yet due to load ordering issues
		FBlueprintCompileReinstancer::Create(NewClass);
	}
}

//UEdGraphSchema_K2* FFSMKismetCompilerContext::CreateSchema()
//{
//	return NewObject<UFSMGraphSchema_K2>();
//}


bool FFSMKismetCompilerContext::IsNodePure(const UEdGraphNode* Node) const
{
	if(Node->IsA<UFSMStateNode_Base>())
	{
		return true;
	}
	return Super::IsNodePure(Node);
}

bool FFSMKismetCompilerContext::ShouldForceKeepNode(const UEdGraphNode* Node) const
{
	return Super::ShouldForceKeepNode(Node);
	//return Node->IsA<UFSMStateNode_Base>();
}

void FFSMKismetCompilerContext::MergeUbergraphPagesIn(UEdGraph* Ubergraph)
{
	Super::MergeUbergraphPagesIn(Ubergraph);

	UEdGraph* RootFSMGraph = GetBlueprint<UFSMBlueprint>()->RootFSMGraph;
	if (RootFSMGraph)
	{
		TArray<UFSMStateNode*> nodes;
		RootFSMGraph->GetNodesOfClass<UFSMStateNode>(nodes);
		for (auto& item : nodes)
		{
			if (UEdGraph* boundgraph = item->GetBoundGraph())
			{
				MergeGraphIntoUbergraph(boundgraph, Ubergraph);
			}
		}
	}

}

void FFSMKismetCompilerContext::CreateFunctionList()
{
	Super::CreateFunctionList();
	UEdGraph* RootFSMGraph = GetBlueprint<UFSMBlueprint>()->RootFSMGraph;
	UFSMBlueprintGeneratedClass* BPClass = Cast<UFSMBlueprintGeneratedClass>(NewClass);
	if (RootFSMGraph && BPClass)
	{
		TArray<UFSMTransitionNode*> nodes;
		RootFSMGraph->GetNodesOfClass<UFSMTransitionNode>(nodes);
		for (auto& item : nodes)
		{
			if (UEdGraph* boundgraph = item->GetBoundGraph())
			{
				ProcessOneFunctionGraph(boundgraph);
			}
		}

		BPClass->States.Empty();
		BPClass->Transitions.Empty();


		TArray<UFSMStateNode_Base*> StateNodeArray;
		RootFSMGraph->GetNodesOfClass<UFSMStateNode_Base>(StateNodeArray);
		for (auto& StateNode : StateNodeArray)
		{
			if (UFSMStateEntryNode* EntryNode = Cast<UFSMStateEntryNode>(StateNode))
			{
				if (!EntryNode->GetOutputPin()->LinkedTo.IsEmpty())
				{
					BPClass->EnteryStateGUID = EntryNode->GetOutputPin()->LinkedTo[0]->GetOwningNode()->NodeGuid;
				}
				else
				{
					ensure(false);
				}
			}
			else if (UFSMTransitionNode* TransitionNode = Cast<UFSMTransitionNode>(StateNode))
			{
				int index = BPClass->Transitions.Emplace(TransitionNode->GetNodeName(), TransitionNode->NodeGuid);
				FFSMTransitionClass& FSMTransitionClass = BPClass->Transitions[index];
				FSMTransitionClass.NextNodeGUID = TransitionNode->GetNextState()->NodeGuid;
			}
			else if (UFSMStateNode* FSMStateNode = Cast<UFSMStateNode>(StateNode))
			{
				int index = BPClass->States.Emplace(FSMStateNode->GetNodeName(), FSMStateNode->NodeGuid);
				FFSMStateClass& FSMStateClass = BPClass->States[index];

				for (auto& item : FSMStateNode->GetOutputPin()->LinkedTo)
				{
					UFSMTransitionNode* transitionNode = Cast<UFSMTransitionNode>(item->GetOwningNode());
					FSMStateClass.ConnectedTransitionGUID.Add(transitionNode->NodeGuid);
				}
			}
			else if (UFSMTransitionResultNode* TransitionResultNode = Cast<UFSMTransitionResultNode>(StateNode))
			{

				UFunction* findfuction = BPClass->FindFunctionByName(TransitionResultNode->transitionName);
				if (!findfuction)
				{
					return;
				}

				FFSMTransitionClass* transtion = BPClass->Transitions.FindByKey(TransitionResultNode->transitionGuid);
				if (!transtion)
				{
					return;
				}
				transtion->TransitionCondition = findfuction;

				BPClass->RemoveFunctionFromFunctionMap(findfuction);
			}
			//StateNode->Compile(Context);
		}

	}


}

void FFSMKismetCompilerContext::CompileFunction(FKismetFunctionContext& Context)
{
	Super::CompileFunction(Context);
}

