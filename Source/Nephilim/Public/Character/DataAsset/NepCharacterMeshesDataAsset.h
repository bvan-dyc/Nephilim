#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NepCharacterMeshesDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepCharacterMeshesDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TArray<class USkeletalMesh*> MeshesToAdd;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<class USkeletalMesh*> MeshesToRemove;

};
