#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/ArcBaseComponent.h"
#include "Item/NepItem.h"
#include "NepContainerInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNepContainerDelegate);

UCLASS(ClassGroup = "ArcECS", meta = (BlueprintSpawnableComponent))
class NEPHILIM_API UNepContainerInventoryComponent : public UArcBaseComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FNepContainerDelegate OnOpenedOnClient;
	
	UPROPERTY(BlueprintAssignable)
	FNepContainerDelegate OnClosedOnClient;

protected:

	UPROPERTY()
	class UNepInventory* Inventory;

	//UPROPERTY(EditDefaultsOnly)
	//TArray<FNepItem>

	bool bIsOpened = false;

public:
	
	virtual void AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;
	virtual void RemoveComponentsFromEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;

//protected:

	void SetIsOpened(bool bInIsOpened);
	bool IsOpened() const { return bIsOpened; }
	
};
