#include "Inventory/NepInventory.h"
#include "ArcECSSubsystem.h"
#include "Inventory/Component/NepItemContainer.h"
#include "Inventory/Resource/NepInventoryEvents.h"
#include "Resource/ArcCoreData.h"
#include "Net/UnrealNetwork.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdateManager.h"
#include "UI/Resource/NepWidgetData.h"

UNepInventory* UNepInventory::GetInventory(AActor& Actor)
{
	UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(Actor.GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	FArcCoreData* CoreData = Universe ? Universe->GetResource<FArcCoreData>() : nullptr;
	const FArcEntityHandle* Entity = CoreData ? CoreData->EntitiesByActor.Find(&Actor) : nullptr;
	const FNepItemContainer* ItemContainer = Entity ? Universe->GetComponent<FNepItemContainer>(*Entity) : nullptr;
	return ItemContainer ? ItemContainer->Inventory.Get() : nullptr;
}

int32 UNepInventory::GetIndexOfItem(const FNepItemID& ItemID) const
{
	for (int32 i = 0; i < ItemArray.Items.Num(); ++i)
	{
		const FNepItem& Item = ItemArray.Items[i];
		if (Item.ID == ItemID) { return i; }
	}
	return INDEX_NONE;
}

FNepItem* UNepInventory::GetItem(const FNepItemID& ItemID)
{
	for (int32 i = 0; i < ItemArray.Items.Num(); ++i)
	{
		FNepItem& Item = ItemArray.Items[i];
		if (Item.ID == ItemID) { return &Item; }
	}
	return nullptr;
}

void UNepInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UNepInventory, ItemArray);
}

void UNepInventory::OnRep_Inventory()
{
	if (FNepInventoryEvents* InventoryEvents = FNepInventoryEvents::Get(this))
	{
		InventoryEvents->ChangedInventories.AddUnique(this);
	}
	if (const FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
	{
		WidgetData->WidgetUpdateManager->TriggerWidgetUpdateEvent(FNepUIEvent_InventoryChanged());
	}
}
