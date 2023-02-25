#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"

#include "NepDialogueBubbleWidget.generated.h"

UCLASS()
class NEPHILIM_API UNepDialogueBubbleWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    void ShowMessage(const UNepDialogueDataAsset* dialogue
        /*const struct FNepDialogueData& dialogueData*/);
    void SetTitle(const FText& title) const;
    void SetDialogue(const FText& dialogue) const;
    void SetImage(UTexture2D* image) const;

    void CloseBubble();

protected:

    UPROPERTY(meta = (BindWidgetOptional))
    class UTextBlock* Title;

    UPROPERTY(meta = (BindWidgetOptional))
    class UTextBlock* Content;

    UPROPERTY(meta = (BindWidgetOptional))
    class UImage* SpeakerImage;
};
