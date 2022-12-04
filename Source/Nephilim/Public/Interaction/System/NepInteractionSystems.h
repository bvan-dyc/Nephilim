#pragma once

#include "ArcRes.h"
#include "Resource/ArcCoreData.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Interaction/Resource/NepCurrentInteractableData.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "UI/Resource/NepWidgetData.h"

struct FNepInteractionSystems
{
	// Tick
	static void DetectInteractable(
		FArcUniverse& Universe,
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
		FArcRes<FNepInteractionEvents> Events);
	
	static void UpdateInteractionMenu(
		FArcUniverse& Universe,
		FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
		FArcRes<FNepInteractionEvents> Events,
		FArcRes<FNepWidgetData> WidgetData);
	
	static void TriggerInteraction(
		FArcUniverse& Universe,
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
		FArcRes<FNepInteractionEvents> Events,
		FArcRes<FNepWidgetData> WidgetData);

	// These specific interaction systems should probably be moved to somewhere else.
	static void ExecuteLootCommand(
		FArcUniverse& Universe,
		FArcRes<FNepCurrentInteractableData> CurrentInteractableData,
		FArcRes<FNepInteractionEvents> InteractionEvents,
		FArcRes<FNepCharacterEvents> CharacterEvents);
	
	static void ExecutePossessCommands(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> Events);
	static void UpdateLights(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> Events);
	
	static void UpdateInteractableIndicator(FArcRes<FNepWidgetData> WidgetData);
	static void ClearEvents(FArcRes<FNepInteractionEvents> Events);
};
