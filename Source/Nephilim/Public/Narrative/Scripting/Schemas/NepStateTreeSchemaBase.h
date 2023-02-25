#pragma once

#include "StateTreeSchema.h"

#include "NepStateTreeSchemaBase.generated.h"

UCLASS(BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Base Schema"))
class NEPHILIM_API UNepStateTreeSchemaBase : public UStateTreeSchema
{
	GENERATED_BODY()

#if WITH_EDITOR
	//These must be overriden in order for them to be shown and be accessible within the editor.
	virtual bool AllowEvaluators() const override { return true; };
	virtual bool AllowMultipleTasks() const override { return true; };
	virtual bool AllowEnterConditions() const override { return true; };
#endif // WITH_EDITOR
	
	virtual bool IsStructAllowed(const UScriptStruct* inScriptStruct) const override;
	virtual bool IsExternalItemAllowed(const UStruct& inStruct) const override;
};
