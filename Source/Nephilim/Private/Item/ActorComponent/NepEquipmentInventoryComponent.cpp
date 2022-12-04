#include "Item/ActorComponent/NepEquipmentInventoryComponent.h"
#include "Net/UnrealNetwork.h"

/*void UNepCharacterComponent::Server_RemoveMeshes_Implementation()
{
    MeshCollections.Reset();
    OnRep_MeshCollections();
}

void UNepCharacterComponent::Server_SetMeshes_Implementation(const UNepCharacterMeshesDataAsset* Meshes)
{
    MeshCollections.Add(Meshes);
    OnRep_MeshCollections();
}*/

void UNepEquipmentInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(UNepEquipmentInventoryComponent, BodyItem);
    
	//FDoRepLifetimeParams SharedParams;
	//DOREPLIFETIME_WITH_PARAMS_FAST(UNepCharacterDataConfig, MeshCollections, SharedParams);
}

void UNepEquipmentInventoryComponent::OnRep_Item()
{
}

/*void UNepCharacterComponent::OnRep_MeshCollections()
{
    UNepCoreSubsystem* CoreSubsystem = UWorld::GetSubsystem<UNepCoreSubsystem>(GetWorld());
    FArcWorld* World = CoreSubsystem ? &CoreSubsystem->GetECSWorld() : nullptr;
    if (FNepCharacterEvents* Events = World ? World->GetResource<FNepCharacterEvents>() : nullptr)
    {
        Events->CharacterMeshesChangedEvents.Add(GetEntityHandle());
    }
}*/

