#pragma once

#include "ArcRes.h"
#include "Character/Resource/NepCharacterEvents.h"

struct FNepCharacterSystems
{
	// Tick
	static void OnCharacterCreated(class FArcUniverse& Universe, FArcRes<FNepCharacterEvents> Events);
	static void UpdateCharacterMeshes(class FArcUniverse& Universe, FArcRes<FNepCharacterEvents> Events);
	static void ClearEvents(FArcRes<FNepCharacterEvents> Events);
	
};
