#include "UI/Widget/NepEquipmentWidget.h"
#include "Character/Actor/NepCharacter.h"
#include "Item/ActorComponent/NepEquipmentInventoryComponent.h"
#include "UI/Resource/NepWidgetData.h"
#include "UI/Widget/NepItemSlotWidget.h"

void UNepEquipmentWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
    
    UpdateItems();
}

void UNepEquipmentWidget::FadeOut()
{
    if (GetRenderOpacity() == 0.0f) { return; }
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
}

void UNepEquipmentWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetRenderOpacity(0.0f);
}

void UNepEquipmentWidget::NativeConstruct()
{
    Super::NativeConstruct();

    
    if (FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
    {
        WidgetData->EquipmentWidget = this;
    }
}

void UNepEquipmentWidget::UpdateItems()
{
    UWorld* World = GetWorld();
    APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
    ANepCharacter* Character = PlayerController ? Cast<ANepCharacter>(PlayerController->GetCharacter()) : nullptr;
    UNepEquipmentInventoryComponent* EquipmentInventory = Character ? Character->FindComponentByClass<UNepEquipmentInventoryComponent>() : nullptr;
    if (EquipmentInventory)
    {
        if (BodySlot)
        {
            //BodySlot->SetItem(EquipmentInventory->BodyItem);
        }
    }
}
