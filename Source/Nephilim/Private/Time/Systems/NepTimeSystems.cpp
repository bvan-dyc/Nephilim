#include "Time/System/NepTimeSystems.h"

#include "Time/Resource/NepTime.h"

void FNepTimeSystems::TickTime(FArcRes<FArcCoreData> CoreData, FArcRes<FNepTime> Time)
{
	const UWorld* World = CoreData->World.Get();
	if (!World) { return; }
	
	Time->DeltaSeconds = World->DeltaTimeSeconds;
	Time->TotalElapsedSeconds += Time->DeltaSeconds;
}
