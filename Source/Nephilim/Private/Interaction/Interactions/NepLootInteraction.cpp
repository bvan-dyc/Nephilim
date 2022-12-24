#include "Interaction/Interactions/NepLootInteraction.h"
#include "Interaction/Actor/NepInventoryInteractionProxy.h"
#include "Interaction/Resource/NepInteractionEvents.h"

TSubclassOf<ANepLongInteractionProxy> FNepLootInteraction::GetLongInteractionProxyClass()
{
	return ANepInventoryInteractionProxy::StaticClass();
}
