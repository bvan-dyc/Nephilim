#include "UI/NepWidgetUpdater.h"
#include "ArcECSSubsystem.h"
#include "ArcUniverse.h"
#include "UI/NepWidgetUpdateManager.h"
#include "UI/Resource/NepWidgetData.h"

FNepWidgetUpdater::~FNepWidgetUpdater()
{
	if (FNepWidgetUpdateManager* UpdateManager = WidgetUpdateManager.Pin().Get())
	{
		UpdateManager->UnregisterUpdater(UpdaterID);
	}
}

TSharedPtr<FNepWidgetUpdater> FNepWidgetUpdater::Create(UWorld* World, FSimpleDelegate UpdateDelegate)
{
    UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(World);
    FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
    const FNepWidgetData* WidgetData = Universe ? Universe->GetResource<FNepWidgetData>() : nullptr;
	if (!WidgetData) { return nullptr; }
	
	TSharedPtr<FNepWidgetUpdater> WidgetUpdater = MakeShared<FNepWidgetUpdater>();
	WidgetUpdater->WidgetUpdateManager = WidgetData->WidgetUpdateManager;
	WidgetUpdater->UpdateDelegate = UpdateDelegate;
	WidgetUpdater->UpdaterID = WidgetData->WidgetUpdateManager->RegisterUpdater(WidgetUpdater);
	
	return WidgetUpdater;
}

void FNepWidgetUpdater::CallUpdateFunction() const
{
	UpdateDelegate.ExecuteIfBound();
}
