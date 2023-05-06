#include "UI/Widget/NepEquipmentWidget.h"

#include "ArcECSSubsystem.h"
#include "Character/Actor/NepCharacter.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Inventory/NepInventory.h"
#include "Inventory/ActorComponent/NepEquipmentComponent.h"
#include "Inventory/ItemConfig/NepArmorItemConfig.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdater.h"
#include "UI/Widget/NepItemSlotWidget.h"

void UNepEquipmentWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetRenderOpacity(0.0f);

    if (HeadSlot)
    {
        HeadSlot->SetSlotIndex(0);
        HeadSlot->OnItemSlotClicked.BindUObject(this, &UNepEquipmentWidget::HandleItemSlotClicked);
    }
    if (BodySlot)
    {
        BodySlot->SetSlotIndex(1);
        BodySlot->OnItemSlotClicked.BindUObject(this, &UNepEquipmentWidget::HandleItemSlotClicked);
    }
    if (LegsSlot)
    {
        LegsSlot->SetSlotIndex(2);
        LegsSlot->OnItemSlotClicked.BindUObject(this, &UNepEquipmentWidget::HandleItemSlotClicked);
    }
    
    WidgetUpdater = FNepWidgetUpdater::Create(GetWorld(), FSimpleDelegate::CreateUObject(this, &UNepEquipmentWidget::Update));
    if (WidgetUpdater)
    {
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_HideUI>();
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_SetRightInventoryPanel>();
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_UpdateEquipment>();
    }
}

void UNepEquipmentWidget::Update()
{
    if (!WidgetUpdater) { return; }

    const bool bHideUI = WidgetUpdater->GetUpdateEvent<FNepUIEvent_HideUI>() != nullptr;
    const TOptional<bool> ShowEquipmentInventory = [&]()->TOptional<bool>
    {
        if (const auto Event = WidgetUpdater->GetUpdateEvent<FNepUIEvent_SetRightInventoryPanel>())
        {
            return Event && Event->RightInventoryPanel == ENepRightInventoryPanel::Equipment;
        }
        return TOptional<bool>();
    }();
    
    if (bIsVisible && (bHideUI || (ShowEquipmentInventory && !*ShowEquipmentInventory)))
    {
        FadeOut();
    }   
    else if (!bIsVisible && !bHideUI && ShowEquipmentInventory && *ShowEquipmentInventory)
    {
        FadeIn();
    }

    if (const auto Event = WidgetUpdater->GetUpdateEvent<FNepUIEvent_UpdateEquipment>())
    {
        ANepCharacter* Character = ANepCharacter::GetLocalCharacter(this);
        UNepInventory* Inventory = Character ? UNepInventory::GetInventory(*Character) : nullptr;
        UNepEquipmentComponent* Equipment = Event->Equipment.Get();

        const FNepItem* HeadItem = nullptr;
        const FNepItem* BodyItem = nullptr;
        const FNepItem* LegsItem = nullptr;
        
        if (Inventory && Equipment)
        {
            HeadItem = Inventory->GetItem(Equipment->HeadItem);
            BodyItem = Inventory->GetItem(Equipment->BodyItem);
            LegsItem = Inventory->GetItem(Equipment->LegsItem);
        }
        
        if (HeadSlot)
        {
            HeadSlot->SetItem(HeadItem);
        }
        if (BodySlot)
        {
            BodySlot->SetItem(BodyItem);
        }
        if (LegsSlot)
        {
            LegsSlot->SetItem(LegsItem);
        }
    }
}

void UNepEquipmentWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
    bIsVisible = true;
}

void UNepEquipmentWidget::FadeOut()
{
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
    bIsVisible = false;
}

void UNepEquipmentWidget::HandleItemSlotClicked(int32 SlotIndex) const
{
    if (!ensure(SlotIndex >= 0 && SlotIndex < 3)) { return; }
    UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
    if (!ECSSubsystem) { return; }
    FArcUniverse& Universe = ECSSubsystem->GetUniverse();
    ANepCharacter* Character = ANepCharacter::GetLocalCharacter(this);
    FArcEntityHandle* Entity = Character ? ECSSubsystem->FindEntityForActor(*Character) : nullptr;
    if (Entity && Universe.IsValid(*Entity))
    {
        const ENepArmorType ArmorType = [&]
        {
            if (SlotIndex == 0) { return ENepArmorType::Head; }
            if (SlotIndex == 1) { return ENepArmorType::Body; }
            if (SlotIndex == 2) { return ENepArmorType::Legs; }
            ensure(false);
            return ENepArmorType::Head;
        }();

        if (FNepCharacterEvents* Events = Universe.GetResource<FNepCharacterEvents>())
        {
            Events->UnequipEvents.Emplace(*Entity, ArmorType);
        }
        
        if (UNepEquipmentComponent* Equipment = Character ? Character->FindComponentByClass<UNepEquipmentComponent>() : nullptr)
        {
            Equipment->Server_UnequipItem(ArmorType);
        }
    }
}
