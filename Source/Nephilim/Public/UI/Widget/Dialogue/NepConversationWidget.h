#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"
#include "NepConversationWidget.generated.h"

UCLASS()
class NEPHILIM_API UNepConversationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void StartDialogue(const UNepDialogueDataAsset* dialogue) const;
	
	void FillWithData(const FText& speakerName, const FText& dialogueText, UTexture2D* speaker) const;
	void EndConversation() const;
	
protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UNepDialogueBubbleWidget* DialogueBubbleWidget = nullptr;
};
