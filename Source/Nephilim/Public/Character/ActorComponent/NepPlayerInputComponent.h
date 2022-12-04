#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "NepPlayerInputComponent.generated.h"

UCLASS()
class UNepPlayerInputComponent : public UInputComponent
{
	GENERATED_BODY()

public:

	void SetupBindings();

private:

	void PossessTarget();
	
};
