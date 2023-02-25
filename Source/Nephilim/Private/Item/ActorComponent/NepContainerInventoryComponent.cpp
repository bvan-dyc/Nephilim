#include "Item/ActorComponent/NepContainerInventoryComponent.h"
#include "ArcUniverse.h"
#include "ArcCommands.h"
#include "Interaction/Component/NepInteractable.h"
#include "Interaction/Interactions/NepLootInteraction.h"
#include "Item/Component/NepItemContainer.h"

void UNepContainerInventoryComponent::AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity)
{
    Universe.GetCommands().AddComponent(Entity, FNepItemContainer { Inventory });
    if (!Universe.HasComponent<FNepInteractable>(Entity))
    {
        Universe.AddComponent(Entity, FNepInteractable { GetOwner() });
    }
    FNepInteractable& Interactable = *Universe.GetComponent<FNepInteractable>(Entity);
    Interactable.Interactions.Add(MakeUnique<FNepLootInteraction>());
}

void UNepContainerInventoryComponent::RemoveComponentsFromEntity(FArcUniverse& Universe, FArcEntityHandle& Entity)
{
    Universe.GetCommands().RemoveComponent<FNepItemContainer>(Entity);
    Universe.GetCommands().RemoveComponent<FNepInteractable>(Entity);
}

void UNepContainerInventoryComponent::SetIsOpened(bool bInIsOpened)
{
    if (bIsOpened == bInIsOpened) { return; }
    bIsOpened = bInIsOpened;
    if (bIsOpened)
    {
        OnOpenedOnClient.Broadcast();
    }
    else
    {
        OnClosedOnClient.Broadcast();
    }
}
