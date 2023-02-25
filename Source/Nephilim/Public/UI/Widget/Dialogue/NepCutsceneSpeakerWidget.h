#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NepCutsceneSpeakerWidget.generated.h"

UCLASS()
class NEPHILIM_API UNepCutsceneSpeakerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetImage(UTexture2D* image) const;

	void HideSpeaker();

protected:

	UPROPERTY(meta = (BindWidget))
	class UImage* SpeakerImage;
};
