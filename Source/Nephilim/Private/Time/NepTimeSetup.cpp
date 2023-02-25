#include "Time/NepTimeSetup.h"

#include "ArcScheduleBuilder.h"
#include "ArcUniverse.h"
#include "Time/Resource/NepTime.h"
#include "Time/System/NepTimeSystems.h"

void FNepTimeSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepTime());
	
	TickScheduleBuilder
		.AddSystem(&FNepTimeSystems::TickTime);
}
