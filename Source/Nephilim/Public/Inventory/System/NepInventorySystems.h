#pragma once

#include "ArcRes.h"
#include "Inventory/Resource/NepInventoryEvents.h"
#include "Resource/ArcCoreData.h"

struct FNepInventorySystems
{
	// Client - Tick
	static void HandleMoveItemCommandsOnClient(
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepInventoryEvents> Events);
	
	static void ClearEvents(FArcRes<FNepInventoryEvents> Events);
};
