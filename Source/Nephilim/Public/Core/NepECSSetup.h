#pragma once

#include "CoreMinimal.h"
#include "ArcECSSetup.h"
#include "NepECSSetup.generated.h"

UCLASS()
class NEPHILIM_API UNepECSSetup : public UArcECSSetup
{
	GENERATED_BODY()

public:

	virtual void SetupECSForGame(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder) override;
	virtual void SetupECSForServer(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder);
	virtual void SetupECSForEditor(FArcUniverse& Universe, UWorld& World, FArcScheduleBuilder& InitScheduleBuilder, FArcScheduleBuilder& TickScheduleBuilder) override;
};
