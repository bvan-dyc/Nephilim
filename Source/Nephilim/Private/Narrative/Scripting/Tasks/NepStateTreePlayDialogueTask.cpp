#include "Narrative/Scripting/Tasks/NepStateTreePlayDialogueTask.h"

#include "ArcECSSubsystem.h"
#include "StateTreeExecutionContext.h"
#include "Narrative/Resource/NepNarrativeEvents.h"

const UStruct* FNepStateTreePlayDialogueTask::GetInstanceDataType() const
{
	return FInstanceDataType::StaticStruct();
}

EStateTreeRunStatus FNepStateTreePlayDialogueTask::Tick(FStateTreeExecutionContext& context, const float deltaTime) const
{
	const FInstanceDataType& instanceData = context.GetInstanceData(*this);
	
	if (!instanceData.DialogueDataAsset)
	{
			
	}

	UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(context.GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	if (!Universe) { return EStateTreeRunStatus::Failed; }
	
	FNepNarrativeEvents* NarrativeEvents = Universe ? Universe->GetResource<FNepNarrativeEvents>() : nullptr;
	if (!NarrativeEvents) { return EStateTreeRunStatus::Failed; }
	
	NarrativeEvents->PlayConversationRequests.Emplace(instanceData.DialogueDataAsset, ENepNarrativeChannel::Cutscene);

	UE_LOG(LogTemp, Log, TEXT("[State Tree] Play Dialogue"))
	
	return EStateTreeRunStatus::Succeeded;
}
