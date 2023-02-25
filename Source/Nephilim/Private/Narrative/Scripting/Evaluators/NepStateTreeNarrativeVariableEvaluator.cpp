#include "Narrative/Scripting/Evaluators/NepStateTreeNarrativeVariableEvaluator.h"

#include "ArcECSSubsystem.h"
#include "StateTreeExecutionContext.h"
#include "Narrative/NepNarrativeTypes.h"
#include "Narrative/Resource/NepNarrative.h"

const UStruct* FNepStateTreeNarrativeVariableEvaluator::GetInstanceDataType() const
{
	return FInstanceDataType::StaticStruct();
}

void FNepStateTreeNarrativeVariableEvaluator::TreeStart(FStateTreeExecutionContext& context) const
{
	Super::TreeStart(context);
	
	FInstanceDataType& currentInstanceData = context.GetInstanceData(*this);
	
	if (!currentInstanceData.VariableID.IsValid() || currentInstanceData.VariableID.IsNone()) { return; }

	UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(context.GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;

	FNepNarrative* Narrative = Universe ? Universe->GetResource<FNepNarrative>() : nullptr;
	if (!Narrative) { return; }
	
	if (Narrative->NarrativeVariables.Contains(currentInstanceData.VariableID))
	{
		UE_LOG(LogTemp, Warning, TEXT("[State Tree Scripting] Trying to create custom variable with a name that already exists: %s"), *currentInstanceData.VariableID.ToString());
		return;
	}
	
	FNepNarrativeVariableData& instanceData = Narrative->NarrativeVariables.Emplace(currentInstanceData.VariableID);
	instanceData.bBool = currentInstanceData.bBool;
	instanceData.Integer = currentInstanceData.Integer;
	instanceData.Double = currentInstanceData.Double;
	instanceData.Vector = currentInstanceData.Vector;
}

void FNepStateTreeNarrativeVariableEvaluator::Tick(FStateTreeExecutionContext& context, const float deltaTime) const
{
	FInstanceDataType& currentInstanceData = context.GetInstanceData(*this);

	if (!currentInstanceData.VariableID.IsValid() || currentInstanceData.VariableID.IsNone()) { return; }
	
	UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(context.GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	FNepNarrative* Narrative = Universe ? Universe->GetResource<FNepNarrative>() : nullptr;
	if (!Narrative) { return; }
	
	const FNepNarrativeVariableData* variableData = Narrative->NarrativeVariables.Find(currentInstanceData.VariableID);
	if (!variableData) { return; }
	
	currentInstanceData.bBool = variableData->bBool;
	currentInstanceData.Integer = variableData->Integer;
	currentInstanceData.Double = variableData->Double;
	currentInstanceData.Vector = variableData->Vector;
}
