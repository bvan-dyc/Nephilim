#include "Character/Component/NepCharacterData.h"
#include "Components/SkeletalMeshComponent.h"

FNepCharacterData::~FNepCharacterData()
{
    DeleteAdditionalCharacterMeshes();
}

void FNepCharacterData::DeleteAdditionalCharacterMeshes()
{
    for (TWeakObjectPtr<USkeletalMeshComponent> MeshWeak : AdditionalCharacterMeshes)
    {
        if (USkeletalMeshComponent* Mesh = MeshWeak.Get())
        {
            Mesh->DestroyComponent();
        }
    }
}
