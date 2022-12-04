#include "Interaction/NepInteractionSetup.h"
#include "ArcUniverse.h"
#include "ArcScheduleBuilder.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Interaction/System/NepInteractionSystems.h"

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
		.AddSystemSeq(&FNepInteractionSystems::ExecuteLootCommand)
		.AddSystemSeq(&FNepInteractionSystems::ExecutePossessCommands)
		.AddSystemSeq(&FNepInteractionSystems::UpdateLights);
}
