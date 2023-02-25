#pragma once

#include "NepNarrativeTypes.generated.h"

UENUM()
enum class ENepNarrativeChannel : uint8
{
	Dialogue,
	Cutscene,
	Chat
};

USTRUCT()
struct NEPHILIM_API FNepNarrativePin
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	const class UNepDialogueDataAsset* OutputDialogue = nullptr;
};

USTRUCT()
struct NEPHILIM_API FNepNarrativeVariableData
{
	GENERATED_BODY()

	FName VariableID;
	
	bool bBool = false;
	
	int32 Integer = 0;
	double Double = 0.0;
	
	FVector Vector = FVector::ZeroVector;
};
