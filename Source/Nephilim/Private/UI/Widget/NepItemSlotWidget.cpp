#include "UI/Widget/NepItemSlotWidget.h"
#include "Components/Image.h"
#include "Item/NepItem.h"
#include "Item/DataAsset/NepItemDataAsset.h"

void UNepItemSlotWidget::SetItem(const FNepItem& Item)
{
    if (Icon && Item.DataAsset)
    {
        Icon->SetBrushFromTexture(Item.DataAsset->Icon);
        Icon->SetVisibility(Item.DataAsset->Icon ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
    }
}
