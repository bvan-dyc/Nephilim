#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArcComponentConfig.generated.h"

// Probably not needed, since there is UArcBaseComponent.
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UArcComponentConfig : public UObject
{
	GENERATED_BODY()
	
public:

	virtual void AddComponentsToEntity(class FArcUniverse& World, class FArcEntityHandle& Entity) const {}
	virtual void RemoveComponentsFromEntity(class FArcUniverse& World, class FArcEntityHandle& Entity) const {}

};
