#include "UI/Widget/NepItemSlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Inventory/NepItem.h"
#include "Inventory/DataAsset/NepItemDataAsset.h"

void UNepItemSlotWidget::SetItem(const FNepItem* Item)
{
    if (!Icon) { return; }
    
    if (Item && Item->DataAsset)
    {
        Icon->SetBrushFromTexture(Item->DataAsset->Icon);
        Icon->SetVisibility(Item->DataAsset->Icon ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
    }
    else
    {
        Icon->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UNepItemSlotWidget::SetSlotIndex(int32 InSlotIndex)
{
    SlotIndex = InSlotIndex;
}

void UNepItemSlotWidget::NativeOnInitialized()
{
    Super::NativePreConstruct();

    if (Button)
    {
        Button->OnClicked.AddDynamic(this, &UNepItemSlotWidget::HandleClicked);
    }
}

void UNepItemSlotWidget::HandleClicked()
{
    OnItemSlotClicked.ExecuteIfBound(SlotIndex);
}
