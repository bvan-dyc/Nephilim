#include "Inventory/NepInventorySetup.h"
#include "ArcScheduleBuilder.h"
#include "Inventory/Resource/NepInventoryEvents.h"
#include "Inventory/System/NepInventorySystems.h"

void FNepInventorySetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepInventoryEvents());

	TickScheduleBuilder
		.AddSystemToStage(TEXT("Nephilim_EventCleanupStage"), &FNepInventorySystems::ClearEvents)

		.AddSystem(&FNepInventorySystems::HandleMoveItemCommandsOnClient, FArcSystemConfig()
			.After(TEXT("InteractionSet_StartInteractions"))
			.Before(TEXT("Interaction_EndLongInteractionsOnClient")));
}

void FNepInventorySetup::SetupForServer(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepInventoryEvents());
}
