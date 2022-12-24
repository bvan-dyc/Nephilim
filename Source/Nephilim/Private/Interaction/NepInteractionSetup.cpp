#include "Interaction/NepInteractionSetup.h"
#include "ArcUniverse.h"
#include "ArcScheduleBuilder.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Interaction/System/NepInteractionSystems.h"
#include "Interaction/System/NepInventoryInteractionSystems.h"
#include "Interaction/System/NepMiscInteractionSystems.h"

void FNepInteractionSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepInteractionEvents());
	Universe.AddResource(FNepCurrentInteractableData());
	
	TickScheduleBuilder
		.AddSystemToStage(FArcScheduleStage::PostUpdateWorkStage, &FNepInteractionSystems::UpdateInteractableIndicator)
		.AddSystemToStage(TEXT("Nephilim_EventCleanupStage"), &FNepInteractionSystems::ClearEvents)

		.AddSystem(&FNepInteractionSystems::DetectInteractable)
		.AddSystemSeq(&FNepInteractionSystems::UpdateInteractionMenu)
		.AddSystemSeq(&FNepInteractionSystems::TriggerInteraction, FArcSystemConfig(TEXT("Interaction_TriggerInteraction")))
		.AddSystemSeq(&FNepInventoryInteractionSystems::StartLootInteractionOnClient)
		.AddSystemSeq(&FNepInteractionSystems::EvaluateLongInteractionConditionsOnClient)
		.AddSystemSeq(&FNepInventoryInteractionSystems::EndLootInteractionOnClient);
}

void FNepInteractionSetup::SetupForServer(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepInteractionEvents());
	Universe.AddResource(FNepServerInteractionData());
	
	TickScheduleBuilder
		.AddSystemToStage(TEXT("Nephilim_EventCleanupStage"), &FNepInteractionSystems::ClearEvents)

		.AddSystem(&FNepMiscInteractionSystems::ExecutePossessCommands)
		.AddSystemSeq(&FNepMiscInteractionSystems::UpdateLights)
		.AddSystemSeq(&FNepInteractionSystems::EvaluateLongInteractionConditionsOnServer)
		.AddSystemSeq(&FNepInteractionSystems::EndLongInteractionsOnServer);
}
