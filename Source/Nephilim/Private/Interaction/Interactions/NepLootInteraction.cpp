#include "Interaction/Interactions/NepLootInteraction.h"
#include "Interaction/Actor/NepInventoryInteractionProxy.h"

TSubclassOf<ANepLongInteractionProxy> FNepLootInteraction::GetLongInteractionProxyClass()
{
	return ANepInventoryInteractionProxy::StaticClass();
}
