#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
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

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<const class UNepItemConfig*> ItemConfigs;

public:
	
	template<typename T>
	const T* GetConfig() const
	{
		for (const class UNepItemConfig* Config : ItemConfigs)
		{
			if (const T* CastedConfig = Cast<T>(Config))
			{
				return CastedConfig;
			}
		}
		return nullptr;
	}
};
