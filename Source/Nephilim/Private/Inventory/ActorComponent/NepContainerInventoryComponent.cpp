#include "Inventory/ActorComponent/NepContainerInventoryComponent.h"
#include "ArcUniverse.h"
#include "ArcCommands.h"
#include "Interaction/Component/NepInteractable.h"
#include "Interaction/Interactions/NepLootInteraction.h"
#include "Inventory/Component/NepItemContainer.h"
#include "Net/UnrealNetwork.h"

UNepContainerInventoryComponent::UNepContainerInventoryComponent()
{
    SetIsReplicatedByDefault(true);
    bReplicateUsingRegisteredSubObjectList = true;
}

void UNepContainerInventoryComponent::AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity)
{
    if (Inventory)
    {
        Universe.GetCommands().AddComponent(Entity, FNepItemContainer(*Inventory));
    }
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

void UNepContainerInventoryComponent::OnRegister()
{
    Super::OnRegister();
    if (Inventory)
    {
        AddReplicatedSubObject(Inventory);
    }
}

void UNepContainerInventoryComponent::OnUnregister()
{
    Super::OnUnregister();
    if (Inventory)
    {
        RemoveReplicatedSubObject(Inventory);
    }
}

void UNepContainerInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UNepContainerInventoryComponent, Inventory);
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
