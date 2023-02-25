#include "Character/System/NepCharacterSystems.h"
#include "ArcEntityBuilder.h"
#include "ArcEntityHandleTemplates.h"
#include "ArcUniverse.h"
#include "Character/Actor/NepCharacter.h"
#include "Character/Component/NepCharacterData.h"
#include "Character/ActorComponent/NepCharacterComponent.h"
#include "Character/DataAsset/NepCharacterMeshesDataAsset.h"
#include "Components/SkeletalMeshComponent.h"

void FNepCharacterSystems::OnCharacterCreated(FArcUniverse& Universe, FArcRes<FNepCharacterEvents> Events)
{
	for (const auto& Entry : Events->CharacterCreatedEvents)
	{
		const FArcEntityHandle& Entity = Entry.Get<0>();
		ANepCharacter* Character = Entry.Get<1>().Get();
		FNepCharacterData* Data = Entity.GetComponent<FNepCharacterData>(Universe);

		if (Data && Data->Character.IsValid()) { return; }
		
		if (Character && Data)
		{
			Data->Character = Character;
			Data->CharacterConversation = Character->CharacterConversation;
			Events->CharacterMeshesChangedEvents.Add(Entity);
		}
	}
}

void FNepCharacterSystems::UpdateCharacterMeshes(FArcUniverse& Universe, FArcRes<FNepCharacterEvents> Events)
{
	for (const FArcEntityHandle& Entity : Events->CharacterMeshesChangedEvents)
	{
		FNepCharacterData* Data = Entity.GetComponent<FNepCharacterData>(Universe);
		ANepCharacter* Character = Data ? Data->Character.Get() : nullptr;
		const UNepCharacterComponent* Component = Character ? Character->GetConfig<UNepCharacterComponent>() : nullptr;

		if (Character && Data && Component)
		{
			if (USkeletalMeshComponent* Skeleton = Character->GetMesh())
			{
				Skeleton->SetSkeletalMesh(Component->Skeleton);
				Skeleton->SetAnimInstanceClass(Component->AnimInstance);
				Skeleton->bUseAttachParentBound = true;

				Data->DeleteAdditionalCharacterMeshes();

				TArray<USkeletalMesh*> Meshes;
				for (const UNepCharacterMeshesDataAsset* MeshCollection : Component->MeshCollections)
				{
					if (!MeshCollection) { continue; }
					for (USkeletalMesh* Mesh : MeshCollection->MeshesToAdd)
					{
						Meshes.Add(Mesh);
					}
					for (USkeletalMesh* Mesh : MeshCollection->MeshesToRemove)
					{
						Meshes.RemoveSingleSwap(Mesh);
					}
				}

				EObjectFlags Flags = EObjectFlags::RF_Transient | EObjectFlags::RF_DuplicateTransient;
				for (int32 i = 0; i < Meshes.Num(); ++i)
				{
					if (!Meshes[i]) { continue; }
					USkeletalMeshComponent* MeshComponent = NewObject<USkeletalMeshComponent>(Character, FName(TEXT("CharacterMesh"), i), Flags);
					MeshComponent->SetSkeletalMesh(Meshes[i]);
					MeshComponent->SetLeaderPoseComponent(Skeleton);
					MeshComponent->bUseAttachParentBound = true;
					MeshComponent->SetupAttachment(Character->GetRootComponent());
					MeshComponent->SetWorldTransform(Skeleton->GetComponentTransform());
					MeshComponent->RegisterComponent();
					
					Data->AdditionalCharacterMeshes.Add(MeshComponent);
				}
			}
		}
	}
}

void FNepCharacterSystems::ClearEvents(FArcRes<FNepCharacterEvents> Events)
{
	*Events = FNepCharacterEvents();
}
