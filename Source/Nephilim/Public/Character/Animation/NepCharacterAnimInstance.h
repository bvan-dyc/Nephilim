#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NepCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEPHILIM_API UNepCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	//UPROPERTY(BlueprintReadOnly)
	//float Direction = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float Speed = 0.0f;

	//UPROPERTY(BlueprintReadOnly)
	//bool bIsInCombatStance = false;

	//UPROPERTY(BlueprintReadOnly)
	//bool bDash = false;

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
