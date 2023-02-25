#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Narrative/NepNarrativeTypes.h"
#include "NepDialogueDataAsset.generated.h"

UCLASS()
class NEPHILIM_API UNepDialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Speaker"))
	class UNepSpeakerDataAsset* Speaker = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Text"))
	FText Text = FText::GetEmpty();

	UPROPERTY(EditAnywhere)
	FName SpeakerEmotionID = FName("DEFAULT");
	
	//	@@TODO(vandyck) once we have a proper system for importing dialogue would be nice to have outgoingpins also saved
	UPROPERTY(EditAnywhere)
	FNepNarrativePin OutgoingPin;
};
