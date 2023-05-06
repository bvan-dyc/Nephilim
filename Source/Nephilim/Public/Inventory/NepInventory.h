#pragma once

#include "CoreMinimal.h"
#include "NepItemArray.h"
#include "NepInventory.generated.h"

UCLASS(DefaultToInstanced, EditInlineNew)
class UNepInventory : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, ReplicatedUsing = "OnRep_Inventory")
    FNepItemArray ItemArray;

    UPROPERTY(EditAnywhere)
    int32 Capacity = 25;

public:

    static UNepInventory* GetInventory(class AActor& Actor);

    int32 GetIndexOfItem(const struct FNepItemID& ItemID) const;
    FNepItem* GetItem(const struct FNepItemID& ItemID);
    
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    void OnRep_Inventory();
};
