#include "UI/Widget/NepContainerInventoryWidget.h"
#include "UI/Resource/NepWidgetData.h"

void UNepContainerInventoryWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
}

void UNepContainerInventoryWidget::FadeOut()
{
    if (GetRenderOpacity() == 0.0f) { return; }
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
}

void UNepContainerInventoryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetRenderOpacity(0.0f);
}

void UNepContainerInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if (FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
    {
        WidgetData->ContainerInventoryWidget = this;
    }
}
