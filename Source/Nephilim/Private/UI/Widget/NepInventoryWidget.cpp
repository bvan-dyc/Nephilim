#include "UI/Widget/NepInventoryWidget.h"
#include "ArcECSSubsystem.h"
#include "ArcUniverse.h"
#include "Components/WrapBox.h"
#include "Inventory/NepInventory.h"
#include "Inventory/Resource/NepInventoryEvents.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdater.h"
#include "UI/Resource/NepUIGlobals.h"
#include "UI/Widget/NepItemSlotWidget.h"

void UNepInventoryWidget::SetInventory(UNepInventory* Inventory)
{
    CurrentInventory = Inventory;
    UpdateContent(*Inventory);
}

void UNepInventoryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    WidgetUpdater = FNepWidgetUpdater::Create(GetWorld(), FSimpleDelegate::CreateUObject(this, &UNepInventoryWidget::Update));
    if (WidgetUpdater)
    {
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_InventoryChanged>();
    }
}

void UNepInventoryWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
    
    if (!SlotsContainer) { return; }
    SlotsContainer->ClearChildren();
    
    UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
    FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
    const FNepUIGlobals* UIGlobals = Universe ? Universe->GetResource<FNepUIGlobals>() : nullptr;
    if (!UIGlobals || !UIGlobals->ItemSlotWidget) { return; }
    
    for (int32 i = 0; i < NumPreviewSlots; ++i)
    {
        UNepItemSlotWidget* NewSlot = CreateWidget<UNepItemSlotWidget>(this, UIGlobals->ItemSlotWidget);
        SlotsContainer->AddChild(NewSlot);
    }
}

void UNepInventoryWidget::Update()
{
    if (!WidgetUpdater) { return; }

    if (const auto Event = WidgetUpdater->GetUpdateEvent<FNepUIEvent_InventoryChanged>())
    {
        const FNepInventoryEvents* InventoryEvents = FNepInventoryEvents::Get(this);
        if (InventoryEvents && CurrentInventory.IsValid() && InventoryEvents->ChangedInventories.Contains(CurrentInventory))
        {
            UpdateContent(*CurrentInventory.Get());
        }
    }
}

void UNepInventoryWidget::UpdateContent(UNepInventory& Inventory)
{
    if (!SlotsContainer) { return; }
    SlotsContainer->ClearChildren();
    ItemSlots.Empty();

    UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
    FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
    const FNepUIGlobals* UIGlobals = Universe ? Universe->GetResource<FNepUIGlobals>() : nullptr;
    if (!UIGlobals || !UIGlobals->ItemSlotWidget) { return; }

    const int32 Capacity = Inventory.Capacity;

    for (int32 i = 0; i < Capacity; ++i)
    {
        UNepItemSlotWidget* NewSlot = CreateWidget<UNepItemSlotWidget>(this, UIGlobals->ItemSlotWidget);
        if (Inventory.ItemArray.Items.IsValidIndex(i))
        {
            NewSlot->SetItem(&Inventory.ItemArray.Items[i]);
            NewSlot->SetSlotIndex(i);
            NewSlot->OnItemSlotClicked.BindUObject(this, &UNepInventoryWidget::HandleItemSlotClicked);
        }
        SlotsContainer->AddChild(NewSlot);
        ItemSlots.Add(NewSlot);
    }
}

void UNepInventoryWidget::HandleItemSlotClicked(int32 SlotIndex) const
{
    UNepInventory* Inventory = CurrentInventory.Get();
    if (!Inventory || !Inventory->ItemArray.Items.IsValidIndex(SlotIndex)) { return; }
    const FNepItem& Item = Inventory->ItemArray.Items[SlotIndex];
    if (Item.IsValid())
    {
        OnItemClicked.ExecuteIfBound(Item.ID);
    }
}
