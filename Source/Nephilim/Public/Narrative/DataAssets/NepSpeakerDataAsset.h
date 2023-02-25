#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "NepSpeakerDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepSpeakerDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	FName SpeakerID = FName();
	
	UPROPERTY(EditAnywhere)
	FText SpeakerName = FText::GetEmpty();

	UPROPERTY(EditAnywhere)
	UTexture2D* CharacterImage = nullptr;
	
	UPROPERTY(EditAnywhere)
	TMap<FName, UTexture2D*> SpeakerEmotions;
};
