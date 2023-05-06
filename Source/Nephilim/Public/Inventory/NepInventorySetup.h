#pragma once

struct FNepInventorySetup
{
	static void Setup(
		class FArcUniverse& Universe,
		struct FArcScheduleBuilder& InitScheduleBuilder,
		struct FArcScheduleBuilder& TickScheduleBuilder
	);
	
	static void SetupForServer(
		class FArcUniverse& Universe,
		struct FArcScheduleBuilder& InitScheduleBuilder,
		struct FArcScheduleBuilder& TickScheduleBuilder
	);
};
