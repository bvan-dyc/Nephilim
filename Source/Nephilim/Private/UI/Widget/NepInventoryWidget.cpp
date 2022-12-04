#include "UI/Widget/NepInventoryWidget.h"
#include "UI/Resource/NepWidgetData.h"

void UNepInventoryWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
}

void UNepInventoryWidget::FadeOut()
{
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
}

void UNepInventoryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetRenderOpacity(0.0f);
}

void UNepInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if (FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
    {
        WidgetData->InventoryWidget = this;
    }
}
