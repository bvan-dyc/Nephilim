#pragma once

#include "ArcRes.h"
#include "Interaction/Resource/NepInteractionEvents.h"

struct FNepMiscInteractionSystems
{
	static void ExecutePossessCommands(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> Events);
	static void UpdateLights(FArcUniverse& Universe, FArcRes<FNepInteractionEvents> Events);
};
