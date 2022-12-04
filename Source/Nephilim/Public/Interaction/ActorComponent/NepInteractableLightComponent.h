#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/ArcBaseComponent.h"
#include "NepInteractableLightComponent.generated.h"

UCLASS(ClassGroup = "ArcECS", meta = (BlueprintSpawnableComponent))
class NEPHILIM_API UNepInteractableLightComponent : public UArcBaseComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(ReplicatedUsing = "OnRep_Light")
	bool bIsOn = false;
	
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = "OnRep_Light")
	FColor Color;

	UPROPERTY()
	TArray<UStaticMeshComponent*> Meshes;

	UPROPERTY()
	class UPointLightComponent* Light;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* LightOnMaterial;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* LightOffMaterial;

public:

	UNepInteractableLightComponent();

	virtual void AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;
	virtual void RemoveComponentsFromEntity(FArcUniverse& World, FArcEntityHandle& Entity) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void ToggleLight();
	void RandomizeLightColor();

private:
	
	UFUNCTION()
	void OnRep_Light();

	void UpdateLight();
};
