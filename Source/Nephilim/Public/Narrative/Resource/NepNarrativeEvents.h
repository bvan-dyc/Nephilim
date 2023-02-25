#pragma once
#include "Narrative/DataAssets/NepConversationDataAsset.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"

#include "NepNarrativeEvents.generated.h"

USTRUCT()
struct NEPHILIM_API FNepConversationFlowPlayer
{
	GENERATED_BODY()

public:

	bool bIsPlaying() const { return DialogueCursor != nullptr; }
	
	UPROPERTY()
	const UNepConversationDataAsset* CurrentConversation = nullptr;
	
	UPROPERTY()
	const UNepDialogueDataAsset* DialogueCursor = nullptr;
};

USTRUCT()
struct NEPHILIM_API FNepPlayConversationRequest
{
	GENERATED_BODY()

public:

	ENepNarrativeChannel Channel = ENepNarrativeChannel::Dialogue;
	
	UPROPERTY()
	const UNepConversationDataAsset* ConversationDataAsset = nullptr;

	FNepPlayConversationRequest() {}
	FNepPlayConversationRequest(const UNepConversationDataAsset* dialogueDataAsset, ENepNarrativeChannel channel) : Channel(channel), ConversationDataAsset(dialogueDataAsset) {}
};

USTRUCT()
struct NEPHILIM_API FNepShowDialogueRequest
{
	GENERATED_BODY()

public:

	UPROPERTY()
	const UNepDialogueDataAsset* DialogueDataAsset = nullptr;

	FNepShowDialogueRequest() {}
	FNepShowDialogueRequest(const UNepDialogueDataAsset* dialogueDataAsset) : DialogueDataAsset(dialogueDataAsset) {}
};

USTRUCT()
struct NEPHILIM_API FNepNarrativeEvents
{
	GENERATED_BODY()

public:
	
	TArray<FNepPlayConversationRequest> PlayConversationRequests;

	// Inputs
	bool bContinueConversationKeyPressed = false;
	
	// UI
	TArray<FNepShowDialogueRequest> ShowOverworldDialogueRequests;
	TArray<FNepShowDialogueRequest> ShowCutsceneDialogueRequests;
};
