#include "Character/NepCharacterSetup.h"
#include "ArcUniverse.h"
#include "ArcScheduleBuilder.h"
#include "Character/System/NepCharacterSystems.h"

void FNepCharacterSetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepCharacterEvents());
	
	TickScheduleBuilder
		.AddSystemToStage(TEXT("Nephilim_EventCleanupStage"), &FNepCharacterSystems::ClearEvents)
		.AddSystem(&FNepCharacterSystems::OnCharacterCreated)
		.AddSystemSeq(&FNepCharacterSystems::UpdateCharacterMeshes);
}

void FNepCharacterSetup::SetupForEditor(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepCharacterEvents());
	
	TickScheduleBuilder
		.AddSystemToStage(TEXT("Nephilim_EventCleanupStage"), &FNepCharacterSystems::ClearEvents)
		.AddSystem(&FNepCharacterSystems::OnCharacterCreated)
		.AddSystemSeq(&FNepCharacterSystems::UpdateCharacterMeshes);
}
