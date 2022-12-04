#include "UI/Widget/NepTopBarWidget.h"
#include "UI/Resource/NepWidgetData.h"

void UNepTopBarWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
}

void UNepTopBarWidget::FadeOut()
{
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
}

void UNepTopBarWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetRenderOpacity(0.0f);
}

void UNepTopBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if (FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
    {
        WidgetData->TopBarWidget = this;
    }
}
