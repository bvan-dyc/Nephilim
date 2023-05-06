#include "UI/Widget/NepTopBarWidget.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdater.h"

void UNepTopBarWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetRenderOpacity(0.0f);
    
    WidgetUpdater = FNepWidgetUpdater::Create(GetWorld(), FSimpleDelegate::CreateUObject(this, &UNepTopBarWidget::Update));
    if (WidgetUpdater)
    {
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_ShowUI>();
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_HideUI>();
    }
}

void UNepTopBarWidget::Update()
{
    if (!WidgetUpdater) { return; }

    if (WidgetUpdater->GetUpdateEvent<FNepUIEvent_ShowUI>() && !bIsVisible)
    {
        FadeIn();
    }
    if (WidgetUpdater->GetUpdateEvent<FNepUIEvent_HideUI>() && bIsVisible)
    {
        FadeOut();
    }
}

void UNepTopBarWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
    bIsVisible = true;
}

void UNepTopBarWidget::FadeOut()
{
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
    bIsVisible = false;
}
