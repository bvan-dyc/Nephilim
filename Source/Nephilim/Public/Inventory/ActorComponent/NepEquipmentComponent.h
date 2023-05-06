#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/ArcBaseComponent.h"
#include "Inventory/NepItem.h"
#include "Inventory/ItemConfig/NepArmorItemConfig.h"
#include "NepEquipmentComponent.generated.h"

UCLASS(ClassGroup = "ArcECS", meta = (BlueprintSpawnableComponent))
class NEPHILIM_API UNepEquipmentComponent : public UArcBaseComponent
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, ReplicatedUsing = "OnRep_Equipment")
	FNepItemID HeadItem;

	UPROPERTY(EditAnywhere, ReplicatedUsing = "OnRep_Equipment")
	FNepItemID BodyItem;
	
	UPROPERTY(EditAnywhere, ReplicatedUsing = "OnRep_Equipment")
	FNepItemID LegsItem;

public:

	UNepEquipmentComponent();
	
	UFUNCTION(Server, Reliable)
	void Server_EquipItem(FNepItemID ItemID);
	
	UFUNCTION(Server, Reliable)
	void Server_UnequipItem(ENepArmorType ArmorType);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	
	UFUNCTION()
	void OnRep_Equipment();

};
