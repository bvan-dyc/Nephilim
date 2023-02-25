#include "Narrative/Scripting/Schemas/NepStateTreeSchemaBase.h"

#include "StateTreeConditionBase.h"
#include "StateTreeTaskBase.h"

#include "StateTreeEvaluatorBase.h"
#include "Narrative/Scripting/Conditions/NepStateTreeConditionBase.h"
#include "Narrative/Scripting/Evaluators/NepStateTreeEvaluatorBase.h"
#include "Narrative/Scripting/Tasks/NepStateTreeSubtreesTask.h"
#include "Narrative/Scripting/Tasks/NepStateTreeTaskBase.h"

bool UNepStateTreeSchemaBase::IsStructAllowed(const UScriptStruct* inScriptStruct) const
{
	return inScriptStruct->IsChildOf(FStateTreeEvaluatorCommonBase::StaticStruct())
	|| inScriptStruct->IsChildOf(FStateTreeTaskCommonBase::StaticStruct())
	|| inScriptStruct->IsChildOf(FStateTreeConditionCommonBase::StaticStruct())
	|| inScriptStruct->IsChildOf(FNepStateTreeEvaluatorBase::StaticStruct())
	|| inScriptStruct->IsChildOf(FNepStateTreeTaskBase::StaticStruct())
	|| inScriptStruct->IsChildOf(FNepStateTreeConditionBase::StaticStruct())
	|| inScriptStruct->IsChildOf(FNepStateTreeSubtreesTask::StaticStruct());
}

bool UNepStateTreeSchemaBase::IsExternalItemAllowed(const UStruct& inStruct) const
{
	return true;
}
