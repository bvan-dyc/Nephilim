#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
//#include "ArcEntityHandle.h"
#include "NepItemDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* Icon;
	

	/*UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<const class UT2ItemComponentConfig*> ComponentConfigs;

public:
	
	FArcEntityHandle CreateItemEntity(class FArcWorld& World) const;

	template<typename T>
	const T* GetConfig() const
	{
		for (const class UT2ItemComponentConfig* Config : ComponentConfigs)
		{
			if (const T* CastedConfig = Cast<T>(Config))
			{
				return CastedConfig;
			}
		}
		return nullptr;
	}*/

};
