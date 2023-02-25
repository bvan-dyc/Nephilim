#include "Narrative/Scripting/Tasks/NepStateTreeSubtreesTask.h"

const UStruct* FNepStateTreeSubtreesTask::GetInstanceDataType() const
{
	return FStateTreeTaskBase::GetInstanceDataType();
}

bool FNepStateTreeSubtreesTask::Link(FStateTreeLinker& linker)
{
	return FStateTreeTaskBase::Link(linker);
}

EStateTreeRunStatus FNepStateTreeSubtreesTask::EnterState(FStateTreeExecutionContext& context, const FStateTreeTransitionResult& transition) const
{
	return FStateTreeTaskBase::EnterState(context, transition);
}

EStateTreeRunStatus FNepStateTreeSubtreesTask::Tick(FStateTreeExecutionContext& context, const float deltaTime) const
{
	return FStateTreeTaskBase::Tick(context, deltaTime);
}
