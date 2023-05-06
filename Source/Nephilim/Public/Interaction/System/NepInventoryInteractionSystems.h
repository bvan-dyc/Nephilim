#pragma once

#include "ArcRes.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "UI/Resource/NepWidgetData.h"

struct FNepInventoryInteractionSystems
{
	// Client
	static void StartLootInteractionOnClient(
		FArcUniverse& Universe,
		FArcRes<FNepWidgetData> WidgetData,
		FArcRes<FNepInteractionEvents> InteractionEvents,
		FArcRes<FNepCharacterEvents> CharacterEvents);
	static void EndLootInteractionOnClient(
		FArcUniverse& Universe,
		FArcRes<FNepWidgetData> WidgetData,
		FArcRes<FNepInteractionEvents> InteractionEvents);
};
