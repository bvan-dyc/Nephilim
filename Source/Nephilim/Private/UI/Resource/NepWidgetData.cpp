#include "UI/Resource/NepWidgetData.h"
#include "ArcECSSubsystem.h"
#include "UI/NepWidgetUpdateManager.h"

FNepWidgetData::FNepWidgetData()
    : WidgetUpdateManager(MakeShared<FNepWidgetUpdateManager>())
{}

FNepWidgetData* FNepWidgetData::Get(const UObject* context)
{
    UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(context);
    FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
    return Universe ? Universe->GetResource<FNepWidgetData>() : nullptr;
}
