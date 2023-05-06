#include "Inventory/System/NepInventorySystems.h"
#include "Interaction/Actor/NepInventoryInteractionProxy.h"
#include "Interaction/Component/NepInteractor.h"

void FNepInventorySystems::HandleMoveItemCommandsOnClient(
	FArcRes<FArcCoreData> CoreData,
	FArcRes<FNepInventoryEvents> Events)
{
	if (!CoreData->World.IsValid()) { return; }
	UWorld& World = *CoreData->World.Get();

	ANepInventoryInteractionProxy* Proxy = FNepInteractor::GetLocalProxy<ANepInventoryInteractionProxy>(&World);
	if (!Proxy) { return; }
	
	for (const auto& [ItemID, bMoveToInteractable] : Events->ItemMoveCommandsOnClient)
	{
		Proxy->MoveItem(ItemID, bMoveToInteractable);
	}
}

void FNepInventorySystems::ClearEvents(FArcRes<FNepInventoryEvents> Events)
{
	*Events = FNepInventoryEvents();
}
