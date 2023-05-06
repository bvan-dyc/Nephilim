#pragma once

#include "CoreMinimal.h"

struct FNepWidgetData
{
public:

    TSharedRef<struct FNepWidgetUpdateManager> WidgetUpdateManager;
    
    TWeakObjectPtr<class UNepHUDWidget> HUDWidget;
    TWeakObjectPtr<class UNepInteractionMenuWidget> InteractionMenuWidget;
    TWeakObjectPtr<class UNepConversationWidget> ConversationWidget;
    TWeakObjectPtr<class UNepCutsceneConversationWidget> CutsceneConversationWidget;
    
    bool bUIVisible = false;

public:

    FNepWidgetData();
    
    static FNepWidgetData* Get(const UObject* context);
};
