#pragma once

#include "ArcRes.h"
#include "Resource/ArcCoreData.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "UI/Resource/NepUIGlobals.h"
#include "UI/Resource/NepWidgetData.h"

struct FNepUISystems
{
	// Init
	static void InitializeUI(FArcRes<FArcCoreData> CoreData, FArcRes<FNepUIGlobals> UIGlobals, FArcRes<FNepWidgetData> WidgetData);

	// Tick
	static void ToggleUI(FArcRes<FArcCoreData> CoreData, FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepCharacterEvents> Events);
};
