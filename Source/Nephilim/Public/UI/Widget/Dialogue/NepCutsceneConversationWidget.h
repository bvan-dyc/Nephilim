#pragma once

#include "CoreMinimal.h"
#include "NepCutsceneSpeakerWidget.h"

#include "Blueprint/UserWidget.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"

#include "NepCutsceneConversationWidget.generated.h"

UCLASS()
class NEPHILIM_API UNepCutsceneConversationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void StartDialogue(const UNepDialogueDataAsset* dialogue) const;
	
	void FillWithData(const FText& speakerName, const FText& dialogueText, const UNepSpeakerDataAsset* leftHandSpeaker, const UNepSpeakerDataAsset* rightHandSpeaker) const;

	void EndConversation() const;

protected:

	UPROPERTY(meta = (BindWidget))
	class UNepDialogueBubbleWidget* DialogueBubbleWidget = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	class UNepCutsceneSpeakerWidget* LeftHandSpeaker = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UNepCutsceneSpeakerWidget* RightHandSpeaker = nullptr;
		
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	void CloseCutscene() const;
};
