#pragma once

#include "CoreMinimal.h"
#include "NepItemConfig.h"
#include "NepArmorItemConfig.generated.h"

UENUM()
enum class ENepArmorType : uint8
{
	Head,
	Body,
	Legs
};

UCLASS()
class UNepArmorItemConfig : public UNepItemConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	ENepArmorType ArmorType = ENepArmorType::Head;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<const class UNepCharacterMeshesDataAsset> MeshesDataAsset = nullptr;
};
