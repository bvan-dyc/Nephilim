#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/ArcBaseComponent.h"
#include "Item/NepItem.h"
#include "NepContainerInventoryComponent.generated.h"

UCLASS(ClassGroup = "ArcECS", meta = (BlueprintSpawnableComponent))
class NEPHILIM_API UNepContainerInventoryComponent : public UArcBaseComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	class UNepInventory* Inventory;

	//UPROPERTY(EditDefaultsOnly)
	//TArray<FNepItem>

public:
	
	virtual void AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;
	virtual void RemoveComponentsFromEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;
	
};
