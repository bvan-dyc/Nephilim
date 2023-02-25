#include "Core/NepECSSetup.h"
#include "ArcScheduleBuilder.h"
#include "Character/NepCharacterSetup.h"
#include "Interaction/NepInteractionSetup.h"
#include "Narrative/NepNarrativeSetup.h"
#include "Time/NepTimeSetup.h"
#include "UI/NepUISetup.h"

void UNepECSSetup::SetupECSForGame(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	TickScheduleBuilder
		.AddUnrealStages()
		.AddStageAfter(TEXT("Nephilim_EventCleanUpStage"), FArcScheduleStage::LastDemotableStage);

	FNepTimeSetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
	FNepCharacterSetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
	FNepUISetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
	FNepInteractionSetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
	FNepNarrativeSetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
}

void UNepECSSetup::SetupECSForServer(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	TickScheduleBuilder
		.AddUnrealStages()
		.AddStageAfter(TEXT("Nephilim_EventCleanUpStage"), FArcScheduleStage::LastDemotableStage);

	FNepCharacterSetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
	FNepInteractionSetup::SetupForServer(Universe, InitScheduleBuilder, TickScheduleBuilder);
	FNepNarrativeSetup::Setup(Universe, InitScheduleBuilder, TickScheduleBuilder);
}

void UNepECSSetup::SetupECSForEditor(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	TickScheduleBuilder
		.AddStageAfter(TEXT("Nephilim_EventCleanUpStage"), FArcScheduleStage::DefaultStage);

	FNepCharacterSetup::SetupForEditor(Universe, InitScheduleBuilder, TickScheduleBuilder);
}
