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
	
		.AddSystemSet(FArcSystemSet()
			.WithLabel(TEXT("InteractionSet_StartInteractions"))
			.After(TEXT("Interaction_TriggerInteraction"))
			.Before(TEXT("Interaction_EvaluateConditionsOnClient"))
			
			.AddSystem(&FNepInventoryInteractionSystems::StartLootInteractionOnClient)
		)
	
		.AddSystem(&FNepInteractionSystems::EvaluateLongInteractionConditionsOnClient, FArcSystemConfig(TEXT("Interaction_EvaluateConditionsOnClient")))
		.AddSystemSeq(&FNepInteractionSystems::EndLongInteractionsOnClient, FArcSystemConfig(TEXT("Interaction_EndLongInteractionsOnClient")))
	
		.AddSystemSet(FArcSystemSet()
			.WithLabel(TEXT("Interaction_CustomEndLongInteractionsOnClient_Set"))
			.After(TEXT("Interaction_EndLongInteractionsOnClient"))
			.Before(TEXT("Interaction_CleanUpLongInteractionsOnClient"))
			
			.AddSystem(&FNepInventoryInteractionSystems::EndLootInteractionOnClient)
		)
	
		.AddSystem(&FNepInteractionSystems::CleanUpLongInteractionsOnClient, FArcSystemConfig(TEXT("Interaction_CleanUpLongInteractionsOnClient")));
	
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
		.AddSystemSeq(&FNepInteractionSystems::EndLongInteractionsOnServer)
		.AddSystemSeq(&FNepInteractionSystems::CleanUpLongInteractionsOnServer);
}
