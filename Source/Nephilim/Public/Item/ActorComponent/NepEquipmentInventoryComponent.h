#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/ArcBaseComponent.h"
#include "Item/NepItem.h"
#include "NepEquipmentInventoryComponent.generated.h"

UCLASS(ClassGroup = "ArcECS", meta = (BlueprintSpawnableComponent))
class NEPHILIM_API UNepEquipmentInventoryComponent : public UArcBaseComponent
{
	GENERATED_BODY()
	
public:

	//UPROPERTY(EditAnywhere, ReplicatedUsing = "OnRep_Item")
	//FNepItem BodyItem;

public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	
	UFUNCTION()
	void OnRep_Item();

	/*UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties))
	FNepCharacterData Data;

	UPROPERTY(EditAnywhere)
	class USkeletalMesh* Skeleton = nullptr;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAnimInstance> AnimInstance = nullptr;

	UPROPERTY(EditAnywhere, ReplicatedUsing = "OnRep_MeshCollections")
	TArray<const class UNepCharacterMeshesDataAsset*> MeshCollections;

public:

	UNepCharacterDataConfig();

	//virtual void AddComponents(FArcWorld& World, FArcEntityBuilder& EntityBuilder) const override;
	virtual void AddComponentToEntity(FArcWorld& World, FArcEntityHandle& Entity) const override;
	virtual void RemoveComponentFromEntity(FArcWorld& World, FArcEntityHandle& Entity) const override;

	UFUNCTION(Server, Reliable)
	void Server_RemoveMeshes();
	
	UFUNCTION(Server, Reliable)
	void Server_SetMeshes(const UNepCharacterMeshesDataAsset* Meshes);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UFUNCTION()
	void OnRep_MeshCollections();*/

};
