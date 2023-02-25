#pragma once

#include "ArcRes.h"
#include "Resource/ArcCoreData.h"
#include "Time/Resource/NepTime.h"

struct FNepTimeSystems
{
	static void TickTime(FArcRes<FArcCoreData> CoreData, FArcRes<FNepTime> Time);
};
