#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"

#include "NepDialogueBubbleWithHeadWidget.generated.h"

UCLASS()
class NEPHILIM_API UNepDialogueBubbleWithHeadWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    void ShowMessage(const UNepDialogueDataAsset* dialogueData
        /*const struct FNepDialogueData& dialogueData*/);

    void SetTitle(const FText& title) const;
    void SetDialogue(const FText& dialogue) const;
    void SetImage(UTexture2D* image) const;
    
    void CloseBubble();

protected:

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Title;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Content;

    UPROPERTY(meta = (BindWidget))
    class UImage* SpeakerImage;
};
