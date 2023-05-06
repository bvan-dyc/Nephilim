#include "Interaction/Actor/NepInventoryInteractionProxy.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Interaction/NepInteractionHelper.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Inventory/NepInventory.h"
#include "Inventory/ActorComponent/NepContainerInventoryComponent.h"

void FNepMoveItemInventoryCommand::Send(ANepInventoryInteractionProxy& Proxy) const
{
	Proxy.Server_MoveItem(ItemID, bToTarget);
}

bool ANepInventoryInteractionProxy::EvaluateLongInteractionConditionsOnClient(const FArcUniverse& Universe, FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity) const
{
	const FNepCharacterEvents* Events = Universe.GetResource<FNepCharacterEvents>();
	if (Events && Events->SetUIVisibilityCommand.IsSet() && !(*Events->SetUIVisibilityCommand)) { return false; }
	return true;
}

bool ANepInventoryInteractionProxy::EvaluateLongInteractionConditionsOnServer(const FArcUniverse& Universe, FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity) const
{
	return FNepInteractionHelper::IsInInteractionRange(Universe, InteractingEntity, InteractableEntity);
}

void ANepInventoryInteractionProxy::OnLongInteractionStartedOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{
	Events.ContainerToLoot = InteractableEntity;
}

void ANepInventoryInteractionProxy::OnLongInteractionEndedOnClient(FArcEntityHandle& InteractingEntity, FArcEntityHandle& InteractableEntity, FNepInteractionEvents& Events) const
{	
	Events.ContainerToStopLooting = InteractableEntity;
}

void ANepInventoryInteractionProxy::MoveItem(const FNepItemID& ItemID, bool bMoveToInteractable)
{
	Server_MoveItem(ItemID, bMoveToInteractable);

	// TODO:
	// if (!CanMoveItem(ItemID, bMoveToInteractable)) { return; }
	//
	// const TSharedPtr<FNepInventoryCommandBase> Command = MakeShared<FNepInventoryCommandBase>(FNepInventoryCommandWrapper(FNepMoveItemInventoryCommand { ItemID, bMoveToInteractable }));
	// CommandBuffer.Add(Command);
	//
	// // Apply command on client.
	//
	// if (!IsClientOnlyProxy())
	// {
	// 	SendPendingCommands();
	// }
}

void ANepInventoryInteractionProxy::Server_MoveItem_Implementation(FNepItemID ItemID, bool bMoveToInteractable)
{
	// if (!CanMoveItem(ItemID, bMoveToInteractable))
	// {
	// 	// TODO: Notify client to undo command if CanMoveItem returns false.
	// 	return;
	// }

	const bool bIsServer = IsNetMode(ENetMode::NM_DedicatedServer);
	UE_LOG(LogTemp, Warning, TEXT("IsServer() %d"), bIsServer);

	AActor* SourceActor = bMoveToInteractable ? InteractorActor : InteractableActor;
	AActor* TargetActor = bMoveToInteractable ? InteractableActor : InteractorActor;
	if (!SourceActor || !TargetActor) { return; }
	
	UNepInventory* SourceInventory = UNepInventory::GetInventory(*SourceActor);
	UNepInventory* TargetInventory = UNepInventory::GetInventory(*TargetActor);
	if (!SourceInventory || !TargetInventory) { return; }

	const int32 ItemIndex = SourceInventory->GetIndexOfItem(ItemID);
	if (ItemIndex == INDEX_NONE) { return; }
	
	const FNepItem& Item = SourceInventory->ItemArray.Items[ItemIndex];
	TargetInventory->ItemArray.Items.Add(Item);
	SourceInventory->ItemArray.Items.RemoveAtSwap(ItemIndex);
	
	SourceInventory->ItemArray.MarkArrayDirty();
	TargetInventory->ItemArray.MarkItemDirty(TargetInventory->ItemArray.Items.Last());

	SourceActor->ForceNetUpdate();
	TargetActor->ForceNetUpdate();
}

void ANepInventoryInteractionProxy::OnReplacedByServer(ANepLongInteractionProxy* ClientOnlyProxy)
{
	if (ANepInventoryInteractionProxy* ProxyCasted = Cast<ANepInventoryInteractionProxy>(ClientOnlyProxy))
	{
		CommandBuffer = ProxyCasted->CommandBuffer;
		SendPendingCommands();
	}
}

void ANepInventoryInteractionProxy::SendPendingCommands()
{
	for (int32 i = NumSent; i < CommandBuffer.Num(); ++i)
	{
		const TSharedPtr<FNepInventoryCommandBase>& command = CommandBuffer[i];
		command->Send(*this);
	}
	NumSent = CommandBuffer.Num();
}

bool ANepInventoryInteractionProxy::CanMoveItem(const FNepItemID& ItemID, bool bMoveToInteractable) const
{
	AActor* SourceActor = bMoveToInteractable ? InteractorActor : InteractableActor;
	AActor* TargetActor = bMoveToInteractable ? InteractableActor : InteractorActor;
	if (!SourceActor || !TargetActor) { return false; }
	
	const UNepInventory* SourceInventory = UNepInventory::GetInventory(*SourceActor);
	const UNepInventory* TargetInventory = UNepInventory::GetInventory(*TargetActor);
	if (!SourceInventory || !TargetInventory) { return false; }
	
	const int32 ItemIndex = SourceInventory->GetIndexOfItem(ItemID);
	if (ItemIndex == INDEX_NONE) { return false; }
	const bool bHasSpace = TargetInventory->ItemArray.Items.Num() < TargetInventory->Capacity;
	if (!bHasSpace) { return false; }

	return true;
}
