#include "Interaction/ActorComponent/NepInteractableLightComponent.h"
#include "ArcEntityBuilder.h"
#include "ArcUniverse.h"
#include "ArcCommands.h"
#include "Components/PointLightComponent.h"
#include "Interaction/Component/NepInteractable.h"
#include "Interaction/Interactions/NepLightInteractions.h"
#include "Net/UnrealNetwork.h"

UNepInteractableLightComponent::UNepInteractableLightComponent()
{
    SetIsReplicatedByDefault(true);
}

void UNepInteractableLightComponent::AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity)
{
    AActor* Owner = GetOwner();
    if (!Owner) { return; }
    
    Meshes.Reset();
    Owner->GetComponents<UStaticMeshComponent>(Meshes);

    Light = Cast<UPointLightComponent>(Owner->FindComponentByClass(UPointLightComponent::StaticClass()));

    if (!Universe.HasComponent<FNepInteractable>(Entity))
    {
        Universe.AddComponent(Entity, FNepInteractable { GetOwner() });
    }
    FNepInteractable& Interactable = *Universe.GetComponent<FNepInteractable>(Entity);
    Interactable.Interactions.Add(MakeUnique<FNepToggleLightInteraction>());
    Interactable.Interactions.Add(MakeUnique<FNepRandomizeLightColorInteraction>());
}

void UNepInteractableLightComponent::ToggleLight()
{
    bIsOn = !bIsOn;
    OnRep_Light();
}

void UNepInteractableLightComponent::RandomizeLightColor()
{
    Color = FColor::MakeRandomColor();
    OnRep_Light();
}

void UNepInteractableLightComponent::RemoveComponentsFromEntity(FArcUniverse& World, FArcEntityHandle& Entity)
{
    World.GetCommands().RemoveComponent<FNepInteractable>(Entity);
}

void UNepInteractableLightComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UNepInteractableLightComponent, bIsOn);
	DOREPLIFETIME(UNepInteractableLightComponent, Color);
}

void UNepInteractableLightComponent::OnRep_Light()
{
    UpdateLight();
}

void UNepInteractableLightComponent::UpdateLight()
{
    for (UStaticMeshComponent* Mesh : Meshes)
    {
        if (!Mesh) { continue; }
        for (int32 i = 0; i < Mesh->GetNumMaterials(); ++i)
        {
            Mesh->SetMaterial(i, bIsOn ? LightOnMaterial : LightOffMaterial);
        }
    }
    if (Light)
    {
        Light->SetVisibility(bIsOn);
        Light->SetLightColor(Color);
    }
}
