#pragma once

#include "CoreMinimal.h"
#include "NepUpdateEventTypeID.h"

struct FNepWidgetUpdateManager
{
private:
	
	struct FNepWidgetUpdaterData
	{
		TWeakPtr<struct FNepWidgetUpdater> WidgetUpdater;
		TArray<FNepUpdateEventTypeID> ListenedEventTypeIDs;
	};

	class FNepWidgetUpdaterArrayBase
	{
	public:
		TArray<int32> UpdaterIDs;
		
	public:
		virtual ~FNepWidgetUpdaterArrayBase() = default;
		virtual void ClearEvent() {}
		virtual bool HasEvent() const { return false; }
	};

	template<typename T>
	class FNepWidgetUpdaterArray : public FNepWidgetUpdaterArrayBase
	{
	public:
		TOptional<T> Event;

	public:
		virtual void ClearEvent() override { Event.Reset(); }
		virtual bool HasEvent() const override { return Event.IsSet(); }
	};

	TArray<FNepWidgetUpdaterData> WidgetUpdaterDatas;
	TArray<int32> FreeUpdaterIndices;

	TMap<FNepUpdateEventTypeID, TSharedRef<FNepWidgetUpdaterArrayBase>> UpdaterArrays;

	TArray<int32> QueuedUpdaters;

public:

	int32 RegisterUpdater(const TSharedPtr<struct FNepWidgetUpdater>& WidgetUpdater);
	void UnregisterUpdater(int32 UpdaterID);

	template<typename T>
	void ConnectUpdaterToEvent(int32 UpdaterID)
	{
		if (!WidgetUpdaterDatas.IsValidIndex(UpdaterID)) { return; }
		const FNepUpdateEventTypeID TypeID = FNepUpdateEventTypeIDHelper::GetUpdateEventTypeID<T>();
		
		FNepWidgetUpdaterData& UpdaterData = WidgetUpdaterDatas[UpdaterID];
		if (!ensure(!UpdaterData.ListenedEventTypeIDs.Contains(UpdaterID))) { return; }
		UpdaterData.ListenedEventTypeIDs.Add(TypeID);
		
		const TSharedRef<FNepWidgetUpdaterArrayBase>& UpdaterArray = UpdaterArrays.FindOrAdd(TypeID, MakeShared<FNepWidgetUpdaterArray<T>>());
		UpdaterArray->UpdaterIDs.Add(UpdaterID);

		if (UpdaterArray->HasEvent())
		{
			QueuedUpdaters.AddUnique(UpdaterID);
		}
	}

	template<typename T>
	void TriggerWidgetUpdateEvent(T&& Event)
	{
		const FNepUpdateEventTypeID TypeID = FNepUpdateEventTypeIDHelper::GetUpdateEventTypeID<T>();
		const TSharedRef<FNepWidgetUpdaterArrayBase>& UpdaterArray = UpdaterArrays.FindOrAdd(TypeID, MakeShared<FNepWidgetUpdaterArray<T>>());
		FNepWidgetUpdaterArray<T>& UpdaterArrayCasted = *static_cast<FNepWidgetUpdaterArray<T>*>(&UpdaterArray.Get());
		UpdaterArrayCasted.Event = MoveTemp(Event);
		
		for (int32 UpdaterID : UpdaterArrayCasted.UpdaterIDs)
		{
			QueuedUpdaters.AddUnique(UpdaterID);
		}
	}

	template<typename T>
	T* GetUpdateEvent()
	{
		const FNepUpdateEventTypeID TypeID = FNepUpdateEventTypeIDHelper::GetUpdateEventTypeID<T>();
		const TSharedRef<FNepWidgetUpdaterArrayBase>* UpdaterArray = UpdaterArrays.Find(TypeID);
		if (!UpdaterArray) { return nullptr; }
		FNepWidgetUpdaterArray<T>& UpdaterArrayCasted = *static_cast<FNepWidgetUpdaterArray<T>*>(&UpdaterArray->Get());
		return UpdaterArrayCasted.Event ? &UpdaterArrayCasted.Event.GetValue() : nullptr;
	}

	void NotifyQueuedUpdaters();
	void ClearQueuedUpdatersAndEvents();
};
