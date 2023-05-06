#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/ArcBaseComponent.h"
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

	UPROPERTY(EditAnywhere, Instanced, Replicated)
	class UNepInventory* Inventory;
	
protected:

	bool bIsOpened = false;

public:

	UNepContainerInventoryComponent();
	
	virtual void AddComponentsToEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;
	virtual void RemoveComponentsFromEntity(FArcUniverse& Universe, FArcEntityHandle& Entity) override;

	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

//protected:

	void SetIsOpened(bool bInIsOpened);
	bool IsOpened() const { return bIsOpened; }
	
};
