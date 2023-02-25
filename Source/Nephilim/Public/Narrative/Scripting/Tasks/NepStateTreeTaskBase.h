#pragma once

#include "StateTreeTaskBase.h"

#include "NepStateTreeTaskBase.generated.h"

USTRUCT(meta = (DisplayName = "Base Task"))
struct NEPHILIM_API FNepStateTreeTaskBase : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()
	
public:

	FNepStateTreeTaskBase() = default;
	virtual ~FNepStateTreeTaskBase() override = default;
	
	virtual bool Link(FStateTreeLinker& linker) override;
};
