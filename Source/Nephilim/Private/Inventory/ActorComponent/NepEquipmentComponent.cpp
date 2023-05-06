#include "Inventory/ActorComponent/NepEquipmentComponent.h"
#include "ArcECSSubsystem.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Inventory/NepInventory.h"
#include "Inventory/DataAsset/NepItemDataAsset.h"
#include "Inventory/ItemConfig/NepArmorItemConfig.h"
#include "Net/UnrealNetwork.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdateManager.h"
#include "UI/Resource/NepWidgetData.h"

UNepEquipmentComponent::UNepEquipmentComponent()
{
    SetIsReplicatedByDefault(true);
}

void UNepEquipmentComponent::Server_EquipItem_Implementation(FNepItemID ItemID)
{
    AActor* Owner = GetOwner();
	UNepInventory* Inventory = Owner ? UNepInventory::GetInventory(*Owner) : nullptr;
    const FNepItem* Item = Inventory ? Inventory->GetItem(ItemID) : nullptr;
    const UNepArmorItemConfig* ArmorConfig = Item && Item->DataAsset ? Item->DataAsset->GetConfig<UNepArmorItemConfig>() : nullptr;
    if (ArmorConfig)
    {
        switch (ArmorConfig->ArmorType)
        {
        case ENepArmorType::Head:
            HeadItem = ItemID;
            break;
        case ENepArmorType::Body:
            BodyItem = ItemID;
            break;
        case ENepArmorType::Legs:
            LegsItem = ItemID;
            break;
        }
        
        OnRep_Equipment();
    }
}

void UNepEquipmentComponent::Server_UnequipItem_Implementation(ENepArmorType ArmorType)
{
    FNepItemID* EquippedItemID = [&]()->FNepItemID*
    {
        if (ArmorType == ENepArmorType::Head) { return &HeadItem; }
        if (ArmorType == ENepArmorType::Body) { return &BodyItem; }
        if (ArmorType == ENepArmorType::Legs) { return &LegsItem; }
        return nullptr;
    }();

    if (!EquippedItemID) { return; }
    EquippedItemID->Reset();

    OnRep_Equipment();
}

void UNepEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UNepEquipmentComponent, HeadItem);
    DOREPLIFETIME(UNepEquipmentComponent, BodyItem);
    DOREPLIFETIME(UNepEquipmentComponent, LegsItem);
}

void UNepEquipmentComponent::OnRep_Equipment()
{
    if (const FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
    {
        WidgetData->WidgetUpdateManager->TriggerWidgetUpdateEvent(FNepUIEvent_UpdateEquipment { this });
    }
    
    UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
    FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
    if (FNepCharacterEvents* Events = Universe ? Universe->GetResource<FNepCharacterEvents>() : nullptr)
    {
        Events->CharacterMeshesChangedEvents.AddUnique(GetEntityHandle());
    }
}
