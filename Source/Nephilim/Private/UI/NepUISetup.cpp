#include "UI/NepUISetup.h"
#include "ArcUniverse.h"
#include "ArcScheduleBuilder.h"
#include "UI/Resource/NepUIGlobals.h"
#include "UI/Resource/NepWidgetData.h"
#include "UI/System/NepUISystems.h"

void FNepUISetup::Setup(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepUIGlobals());
	Universe.AddResource(FNepWidgetData());
	
	InitScheduleBuilder
		.AddSystem(&FNepUISystems::InitializeGlobals)
		.AddSystemSeq(&FNepUISystems::CreateHUD);
	
	TickScheduleBuilder
		.AddSystemToStage(FArcScheduleStage::PostUpdateWorkStage, &FNepUISystems::UpdateWidgets)
		.AddSystem(&FNepUISystems::HandleToggleUI, FArcSystemConfig().Before(TEXT("Interaction_TriggerInteraction")))
		.AddSystemSeq(&FNepUISystems::SetUIVisibility, FArcSystemConfig().After(TEXT("Interaction_CustomEndLongInteractionsOnClient_Set")));
}

void FNepUISetup::SetupForEditor(FArcUniverse& Universe, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder)
{
	Universe.AddResource(FNepUIGlobals());
	
	InitScheduleBuilder.AddSystem(&FNepUISystems::InitializeGlobals);
}
