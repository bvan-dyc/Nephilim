#pragma once

#include "NepTime.h"
#include "ArcRes.h"

struct FNepTimer
{

protected:

	TOptional<float> StartTimeSeconds;

	float DurationSeconds = 1.f;

public:
	
	FNepTimer() : DurationSeconds(1.f) {}
	FNepTimer(float duration) : DurationSeconds(duration), StartTimeSeconds(-duration) {}

	void Start(const FArcRes<FNepTime>& NepTime) { StartTimeSeconds = NepTime->TotalElapsedSeconds; }

	bool IsEnded(const FArcRes<FNepTime>& NepTime) const { return !StartTimeSeconds.IsSet() || NepTime->TotalElapsedSeconds >= StartTimeSeconds.GetValue() + DurationSeconds; };
};
