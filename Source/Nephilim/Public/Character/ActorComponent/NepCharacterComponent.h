#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/ArcBaseComponent.h"
#include "Character/Component/NepCharacterData.h"
#include "NepCharacterComponent.generated.h"

UCLASS(ClassGroup = "ArcECS", meta = (BlueprintSpawnableComponent))
class NEPHILIM_API UNepCharacterComponent : public UArcBaseComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties))
	FNepCharacterData Data;

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* Skeleton = nullptr;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAnimInstance> AnimInstance = nullptr;

	UPROPERTY(EditAnywhere, ReplicatedUsing = "OnRep_MeshCollections")
	TArray<const class UNepCharacterMeshesDataAsset*> MeshCollections;

public:

	UNepCharacterComponent();
	
	virtual void AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;
	virtual void RemoveComponentsFromEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;

	UFUNCTION(Server, Reliable)
	void Server_RemoveMeshes();
	
	UFUNCTION(Server, Reliable)
	void Server_SetMeshes(const UNepCharacterMeshesDataAsset* Meshes);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UFUNCTION()
	void OnRep_MeshCollections();
};
