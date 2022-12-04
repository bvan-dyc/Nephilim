#pragma once

#include "CoreMinimal.h"
#include "NepCharacterData.generated.h"

USTRUCT()
struct FNepCharacterData
{
    GENERATED_BODY()

public:
    
    TWeakObjectPtr<class ANepCharacter> Character;
    TArray<TWeakObjectPtr<class USkeletalMeshComponent>> AdditionalCharacterMeshes;

public:

    ~FNepCharacterData();
    void DeleteAdditionalCharacterMeshes();

};
