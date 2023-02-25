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
	
	InitScheduleBuilder.AddSystem(&FNepUISystems::InitializeUI);
	
	TickScheduleBuilder
		.AddSystem(&FNepUISystems::HandleToggleUI, FArcSystemConfig().Before(TEXT("Interaction_TriggerInteraction")))
		.AddSystemSeq(&FNepUISystems::SetUIVisibility, FArcSystemConfig().After(TEXT("Interaction_CustomEndLongInteractionsOnClient_Set")));
}
