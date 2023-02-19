#pragma once

#include "ArcRes.h"
#include "Resource/ArcCoreData.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Interaction/Resource/NepCurrentInteractableData.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Interaction/Resource/NepServerInteractionData.h"
#include "UI/Resource/NepWidgetData.h"

struct FNepInteractionSystems
{
	// Client - Tick
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
	
	static void EvaluateLongInteractionConditionsOnClient(
		FArcUniverse& Universe,
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepServerInteractionData> ServerInteractionData,
		FArcRes<FNepInteractionEvents> Events);
	
	static void EndLongInteractionsOnClient(
		FArcUniverse& Universe,
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepInteractionEvents> Events);
	
	static void CleanUpLongInteractionsOnClient(
		FArcUniverse& Universe,
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepInteractionEvents> Events);

	
	// Server - Tick
	static void EvaluateLongInteractionConditionsOnServer(
		FArcUniverse& Universe,
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepServerInteractionData> ServerInteractionData,
		FArcRes<FNepInteractionEvents> Events);
	
	static void EndLongInteractionsOnServer(
		FArcUniverse& Universe,
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepInteractionEvents> Events);
	
	static void CleanUpLongInteractionsOnServer(
		FArcUniverse& Universe,
		FArcRes<FArcCoreData> CoreData,
		FArcRes<FNepServerInteractionData> ServerInteractionData,
		FArcRes<FNepInteractionEvents> Events);

	
	static void UpdateInteractableIndicator(FArcRes<FNepWidgetData> WidgetData);
	static void ClearEvents(FArcRes<FNepInteractionEvents> Events);
};
