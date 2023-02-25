#pragma once

#include "CoreMinimal.h"
#include "Narrative/DataAssets/NepConversationDataAsset.h"
#include "NepCharacterData.generated.h"

USTRUCT()
struct FNepCharacterData
{
    GENERATED_BODY()

public:
    
    TWeakObjectPtr<class ANepCharacter> Character;
    TArray<TWeakObjectPtr<class USkeletalMeshComponent>> AdditionalCharacterMeshes;
    
    UPROPERTY(EditAnywhere)
    const class UNepConversationDataAsset* CharacterConversation = nullptr;
    
public:

    ~FNepCharacterData();
    void DeleteAdditionalCharacterMeshes();

};
