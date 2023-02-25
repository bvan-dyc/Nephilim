#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NepDialogueOptionButton.generated.h"

UCLASS()
class NEPHILIM_API UNepDialogueOptionButton : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetText(/*const struct FNepDialogueData& dialogueData*/);

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;
};
