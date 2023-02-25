#include "Narrative/System/NepNarrativeSystems.h"

#include "EngineUtils.h"
#include "StateTreeExecutionContext.h"
#include "Character/Component/NepCharacterData.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Narrative/NepNarrativeGlobalsDataAsset.h"
#include "Narrative/NepNarrativeTreeWrapperDataAsset.h"
#include "Narrative/Scripting/Tasks/NepStateTreeContextHandler.h"
#include "Resource/ArcCoreData.h"
#include "Time/Resource/NepTime.h"

void FNepNarrativeSystems::InitNarrativeSystems(FArcRes<FArcCoreData> CoreData, FArcRes<FNepNarrativeGlobals> NarrativeGlobals, FArcRes<FNepNarrative> Narrative)
{
	TArray<UObject*> Assets;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Globals"), Assets, EngineUtils::ATL_Regular);
	for (const auto Asset : Assets)
	{
		if (const UNepNarrativeGlobalsDataAsset* NarrativeGlobalsDataAsset = Cast<UNepNarrativeGlobalsDataAsset>(Asset))
		{
			*NarrativeGlobals = NarrativeGlobalsDataAsset->NarrativeGlobals;
		}
	}
}

void FNepNarrativeSystems::ExecuteTalkCommands(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> InteractionEvents, FArcRes<FNepNarrativeEvents> NarrativeEvents)
{
	for (const TPair<FArcEntityHandle, FArcEntityHandle>& TalkCommand : InteractionEvents->TalkCommands)
	{
		const FNepCharacterData* Interactee = Universe.GetComponent<FNepCharacterData>(TalkCommand.Get<1>());
		
		NarrativeEvents->PlayConversationRequests.Emplace(FNepPlayConversationRequest(Interactee->CharacterConversation, ENepNarrativeChannel::Dialogue));
	}
}

void FNepNarrativeSystems::ConversationTick(FArcRes<FNepNarrative> Narrative, FArcRes<FNepNarrativeEvents> NarrativeEvents)
{
	if (NarrativeEvents->bContinueConversationKeyPressed)
	{
		if (Narrative->CutsceneFlowPlayer.bIsPlaying())
		{
			NarrativeEvents->PlayConversationRequests.Emplace(Narrative->CutsceneFlowPlayer.CurrentConversation, ENepNarrativeChannel::Cutscene);
		}
		if (Narrative->DialogueFlowPlayer.bIsPlaying())
		{
			NarrativeEvents->PlayConversationRequests.Emplace(Narrative->DialogueFlowPlayer.CurrentConversation, ENepNarrativeChannel::Dialogue);
		}
	}
	
	for (const FNepPlayConversationRequest& ConversationRequest : NarrativeEvents->PlayConversationRequests)
	{
		if (ConversationRequest.ConversationDataAsset)
		{
			if (ConversationRequest.Channel == ENepNarrativeChannel::Cutscene)
			{
				if (ConversationRequest.ConversationDataAsset == Narrative->CutsceneFlowPlayer.CurrentConversation && Narrative->CutsceneFlowPlayer.DialogueCursor)
				{
					Narrative->CutsceneFlowPlayer.DialogueCursor = Narrative->CutsceneFlowPlayer.DialogueCursor->OutgoingPin.OutputDialogue;
				}
				else
				{
					Narrative->CutsceneFlowPlayer.DialogueCursor = ConversationRequest.ConversationDataAsset->StartNode;
				}
				
				if (Narrative->CutsceneFlowPlayer.DialogueCursor)
				{
					NarrativeEvents->ShowCutsceneDialogueRequests.Emplace(FNepShowDialogueRequest(Narrative->CutsceneFlowPlayer.DialogueCursor));
				}
				else
				{
					NarrativeEvents->ShowCutsceneDialogueRequests.Emplace(FNepShowDialogueRequest());
				}
			}
			
			if (ConversationRequest.Channel == ENepNarrativeChannel::Dialogue)
			{
				if (ConversationRequest.ConversationDataAsset == Narrative->DialogueFlowPlayer.CurrentConversation && Narrative->DialogueFlowPlayer.DialogueCursor)
				{
					Narrative->DialogueFlowPlayer.DialogueCursor = Narrative->DialogueFlowPlayer.DialogueCursor->OutgoingPin.OutputDialogue;
				}
				else
				{
					Narrative->DialogueFlowPlayer.DialogueCursor = ConversationRequest.ConversationDataAsset->StartNode;
				}

				if (Narrative->DialogueFlowPlayer.DialogueCursor)
				{
					NarrativeEvents->ShowOverworldDialogueRequests.Emplace(FNepShowDialogueRequest(Narrative->DialogueFlowPlayer.DialogueCursor));
				}
				else
				{
					NarrativeEvents->ShowOverworldDialogueRequests.Emplace(FNepShowDialogueRequest());
				}
			}
		}
		else
		{
			if (ConversationRequest.Channel == ENepNarrativeChannel::Dialogue)
			{
				ResetFlowPlayer(Narrative->DialogueFlowPlayer);

				NarrativeEvents->ShowOverworldDialogueRequests.Emplace(FNepShowDialogueRequest());
			}
			if (ConversationRequest.Channel == ENepNarrativeChannel::Cutscene)
			{
				ResetFlowPlayer(Narrative->CutsceneFlowPlayer);

				NarrativeEvents->ShowCutsceneDialogueRequests.Emplace(FNepShowDialogueRequest());
			}
		}
	}
}

void FNepNarrativeSystems::CutscenesTick(FArcRes<FArcCoreData> CoreData, FArcRes<FNepTime> Time, FArcRes<FNepNarrativeGlobals> NarrativeGlobals, FArcRes<FNepNarrative> Narrative, FArcRes<FNepNarrativeEvents> NarrativeEvents)
{
	UWorld* World = CoreData->World.Get();
	if (!World) { return; }

	if (Narrative->bStoppedMainTree) { return; }
	
	const APlayerController* playerController = World->GetFirstPlayerController<APlayerController>();
	if (!playerController) { return; }
	
	if (!NarrativeGlobals->SandboxStateTree || !NarrativeGlobals->SandboxStateTree->SandboxStateTree.IsValid()) { return; }

	const UStateTree* stateTree = NarrativeGlobals->SandboxStateTree->SandboxStateTree.GetStateTree();
	Narrative->NarrativeTree = FNepNarrativeTreeWrapper(World, stateTree);
	FStateTreeExecutionContext masterTreeContext = Narrative->NarrativeTree.ExecutionData.ComposeContext();
	if (!ensure(masterTreeContext.IsValid())) { return; }

 	if (!Narrative->bStartedMainTree)
	{
		masterTreeContext.Start();
	
		Narrative->bStartedMainTree = true;
	}

	const EStateTreeRunStatus masterTreeStatus = masterTreeContext.Tick(Time->DeltaSeconds);
	
	if (masterTreeStatus == EStateTreeRunStatus::Succeeded || masterTreeStatus == EStateTreeRunStatus::Failed)
	{
		// Note if we had more than the master tree we should stop all other trees here as well
		masterTreeContext.Stop();
		Narrative->bStoppedMainTree = true;
	}
}

void FNepNarrativeSystems::ClearEvents(FArcRes<FNepNarrativeEvents> Events)
{
	*Events = FNepNarrativeEvents();
}

// PRIVATE

void FNepNarrativeSystems::ResetFlowPlayer(FNepConversationFlowPlayer& FlowPlayer)
{
	FlowPlayer.CurrentConversation = nullptr;
	FlowPlayer.DialogueCursor = nullptr;
}

void FNepNarrativeSystems::TickEntityTrees(FArcRes<FNepNarrative> Narrative, UWorld* World)
{
	for (FNepEntityScriptingData& scriptingData : Narrative->EntityTrees)
	{
		//@TODO(vandyck) To be Implemented
	}
}

void FNepNarrativeSystems::RemoveEntityTrees(FArcRes<FNepNarrative> Narrative, UWorld* World)
{
	//@TODO(vandyck) To be Implemented
}