#include "Character/ActorComponent/NepCharacterComponent.h"
#include "ArcEntityBuilder.h"
#include "ArcUniverse.h"
#include "ArcCommands.h"
#include "ArcECSSubsystem.h"
#include "Character/Actor/NepCharacter.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Interaction/Component/NepInteractable.h"
#include "Interaction/Component/NepInteractor.h"
#include "Interaction/Interactions/NepPossessInteraction.h"
#include "Net/UnrealNetwork.h"

UNepCharacterComponent::UNepCharacterComponent()
{
    SetIsReplicatedByDefault(true);
}

void UNepCharacterComponent::AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity)
{
    ANepCharacter* Character = Cast<ANepCharacter>(GetOwner());
    if (!Character || !ensure(Universe.IsValid(Entity))) { return; }
    
    Universe.GetCommands().AddComponent(Entity, FNepCharacterData(Data));
    Universe.GetCommands().AddComponent(Entity, FNepInteractor());
    
    if (!Universe.HasComponent<FNepInteractable>(Entity))
    {
        Universe.AddComponent(Entity, FNepInteractable { Character });
    }
    FNepInteractable& Interactable = *Universe.GetComponent<FNepInteractable>(Entity);
    Interactable.Interactions.Add(MakeUnique<FNepPossessInteraction>());
    
    if (FNepCharacterEvents* Events = Universe.GetResource<FNepCharacterEvents>())
    {
        Events->CharacterCreatedEvents.Emplace(Entity, Character);
    }
}

void UNepCharacterComponent::RemoveComponentsFromEntity(FArcUniverse& Universe, FArcEntityHandle& Entity)
{
    Universe.GetCommands().RemoveComponent<FNepCharacterData>(Entity);
    Universe.GetCommands().RemoveComponent<FNepInteractable>(Entity);
}

void UNepCharacterComponent::Server_RemoveMeshes_Implementation()
{
    MeshCollections.Reset();
    OnRep_MeshCollections();
}

void UNepCharacterComponent::Server_SetMeshes_Implementation(const UNepCharacterMeshesDataAsset* Meshes)
{
    MeshCollections.Add(Meshes);
    OnRep_MeshCollections();
}

void UNepCharacterComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UNepCharacterComponent, MeshCollections);
    
	//FDoRepLifetimeParams SharedParams;
	//DOREPLIFETIME_WITH_PARAMS_FAST(UNepCharacterDataConfig, MeshCollections, SharedParams);
}

void UNepCharacterComponent::OnRep_MeshCollections()
{
    UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
    FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
    if (FNepCharacterEvents* Events = Universe ? Universe->GetResource<FNepCharacterEvents>() : nullptr)
    {
        Events->CharacterMeshesChangedEvents.AddUnique(GetEntityHandle());
    }
}

