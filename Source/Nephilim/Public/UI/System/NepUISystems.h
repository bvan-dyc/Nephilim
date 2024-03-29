﻿#pragma once

#include "ArcRes.h"
#include "Resource/ArcCoreData.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "UI/Resource/NepUIGlobals.h"
#include "UI/Resource/NepWidgetData.h"

struct FNepUISystems
{
	// Init
	static void InitializeGlobals(FArcRes<FArcCoreData> CoreData, FArcRes<FNepUIGlobals> UIGlobals);
	static void CreateHUD(FArcRes<FArcCoreData> CoreData, FArcRes<FNepUIGlobals> UIGlobals, FArcRes<FNepWidgetData> WidgetData);

	// Tick
	static void UpdateWidgets(FArcRes<FNepWidgetData> WidgetData);
	static void HandleToggleUI(FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepCharacterEvents> Events);
	static void SetUIVisibility(FArcRes<FArcCoreData> CoreData, FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepCharacterEvents> Events);
};
