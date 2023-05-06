#include "Inventory/Component/NepItemContainer.h"

FNepItemContainer::FNepItemContainer(UNepInventory& InInventory)
{
	Inventory = &InInventory;
	
	UWorld* World = Inventory->GetWorld();
	if (World && World->IsGameWorld())
	{
		const bool bIsServer = World->IsNetMode(ENetMode::NM_DedicatedServer);
		if (bIsServer)
		{
			Inventory->ItemArray.MarkArrayDirty();
		}
		else
		{
			// For some reason all items are duplicated if the inventory isn't emptied here.
			Inventory->ItemArray.Items.Empty();
		}
	}

#if WITH_EDITOR
	if (!World || World->IsGameWorld()) { return; }
	
	for (FNepItem& Item : Inventory->ItemArray.Items)
	{
		if (!Item.ID.IsValid())
		{
			Item.ID = FNepItemID::Create();
		}
	}
#endif
}
