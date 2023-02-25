#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Narrative/NepNarrativeTypes.h"

#include "NepConversationDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepConversationDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	ENepNarrativeChannel ConversationChannel = ENepNarrativeChannel::Dialogue;
		
	UPROPERTY(EditAnywhere)
	class UNepDialogueDataAsset* StartNode = nullptr;
};
