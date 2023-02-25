#pragma once

#include "NepStateTreeTaskBase.h"
#include "Narrative/DataAssets/NepDialogueDataAsset.h"

#include "NepStateTreePlayDialogueTask.generated.h"

USTRUCT()
struct NEPHILIM_API FNepStateTreePlayDialogueTaskInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Parameter")
	class UNepConversationDataAsset* DialogueDataAsset = nullptr;
};

USTRUCT(meta = (DisplayName = "Play Dialogue Task"))
struct NEPHILIM_API FNepStateTreePlayDialogueTask : public FNepStateTreeTaskBase
{
	GENERATED_BODY()
	
public:
	typedef FNepStateTreePlayDialogueTaskInstanceData FInstanceDataType;
	
	FNepStateTreePlayDialogueTask() = default;

	virtual const UStruct* GetInstanceDataType() const override;
	
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& context, const float deltaTime) const override;
};
