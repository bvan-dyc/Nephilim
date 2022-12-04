#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NepPlayerController.generated.h"

UCLASS(config=Game)
class ANepPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
};
