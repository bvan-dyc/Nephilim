#include "Inventory/Resource/NepInventoryEvents.h"
#include "ArcECSSubsystem.h"

FNepInventoryEvents* FNepInventoryEvents::Get(const UObject* context)
{
    UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(context);
    FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
    return Universe ? Universe->GetResource<FNepInventoryEvents>() : nullptr;
}
