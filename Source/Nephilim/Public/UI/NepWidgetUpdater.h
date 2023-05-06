#pragma once

#include "CoreMinimal.h"
#include "NepWidgetUpdateManager.h"

struct FNepWidgetUpdater final
{
private:

	TWeakPtr<FNepWidgetUpdateManager> WidgetUpdateManager;
	FSimpleDelegate UpdateDelegate;

	int32 UpdaterID = INDEX_NONE;

public:
	
	~FNepWidgetUpdater();

	static TSharedPtr<FNepWidgetUpdater> Create(UWorld* World, FSimpleDelegate InUpdateDelegate);

	template<typename T>
	void ListenToUpdateEvent() const
	{
		if (FNepWidgetUpdateManager* UpdateManager = WidgetUpdateManager.Pin().Get())
		{
			UpdateManager->ConnectUpdaterToEvent<T>(UpdaterID);
		}
	}

	template<typename T>
	T* GetUpdateEvent() const
	{
		FNepWidgetUpdateManager* UpdateManager = WidgetUpdateManager.Pin().Get();
		return UpdateManager ? UpdateManager->GetUpdateEvent<T>() : nullptr;
	}

	void CallUpdateFunction() const;
	
};
