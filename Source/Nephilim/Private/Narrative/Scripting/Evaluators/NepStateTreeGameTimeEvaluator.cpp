#include "Narrative/Scripting/Evaluators/NepStateTreeGameTimeEvaluator.h"

#include "ArcECSSubsystem.h"
#include "StateTreeExecutionContext.h"
#include "Time/Resource/NepTime.h"

void FNepStateTreeGameTimeEvaluator::Tick(FStateTreeExecutionContext& context, const float deltaTime) const
{
	UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(context.GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;

	const FNepTime* Time = Universe ? Universe->GetResource<FNepTime>() : nullptr;
	if (!Time) { return; }
	
	FInstanceDataType& instanceData = context.GetInstanceData(*this);
	instanceData.Seconds = Time->TotalElapsedSeconds;
}

const UStruct* FNepStateTreeGameTimeEvaluator::GetInstanceDataType() const
{
	return FInstanceDataType::StaticStruct();
}

void FNepStateTreeGameTimeEvaluator::TreeStart(FStateTreeExecutionContext& context) const
{
	Super::TreeStart(context);

	UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(context.GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;

	const FNepTime* Time = Universe ? Universe->GetResource<FNepTime>() : nullptr;
	if (!Time) { return; }
	
	FInstanceDataType& instanceData = context.GetInstanceData(*this);
	instanceData.Seconds = Time->TotalElapsedSeconds;
}
