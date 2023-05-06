#include "UI/NepWidgetUpdateManager.h"
#include "UI/NepWidgetUpdater.h"
#include "UI/Resource/NepWidgetData.h"

int32 FNepWidgetUpdateManager::RegisterUpdater(const TSharedPtr<FNepWidgetUpdater>& WidgetUpdater)
{
	const int32 UpdaterID = [&]
	{
		if (!FreeUpdaterIndices.IsEmpty())
		{
			return FreeUpdaterIndices.Pop();
		}
		return WidgetUpdaterDatas.Emplace();
	}();
	
	FNepWidgetUpdaterData& UpdaterData = WidgetUpdaterDatas[UpdaterID];
	UpdaterData.WidgetUpdater = WidgetUpdater;
	
	return UpdaterID;
}

void FNepWidgetUpdateManager::UnregisterUpdater(int32 UpdaterID)
{
	if (!WidgetUpdaterDatas.IsValidIndex(UpdaterID)) { return; }
	
	FNepWidgetUpdaterData& UpdaterData = WidgetUpdaterDatas[UpdaterID];
	
	for (const FNepUpdateEventTypeID TypeID : UpdaterData.ListenedEventTypeIDs)
	{
		if (const TSharedRef<FNepWidgetUpdaterArrayBase>* UpdaterArray = UpdaterArrays.Find(TypeID))
		{
			(*UpdaterArray)->UpdaterIDs.Remove(UpdaterID);
			// Empty arrays are removed in ClearQueuedEventsAndUpdaters. Removing them here would also remove the stored event.
		}
	}
	
	UpdaterData.WidgetUpdater.Reset();
	UpdaterData.ListenedEventTypeIDs.Reset();
	
	QueuedUpdaters.RemoveSingleSwap(UpdaterID);
	
	FreeUpdaterIndices.Add(UpdaterID);
}

void FNepWidgetUpdateManager::NotifyQueuedUpdaters()
{
	for (const int32 UpdaterID : QueuedUpdaters)
	{
		if (!WidgetUpdaterDatas.IsValidIndex(UpdaterID)) { continue; }
		const FNepWidgetUpdater* WidgetUpdater = WidgetUpdaterDatas[UpdaterID].WidgetUpdater.Pin().Get();
		if (!WidgetUpdater) { continue; }
		WidgetUpdater->CallUpdateFunction();
	}
}

void FNepWidgetUpdateManager::ClearQueuedUpdatersAndEvents()
{
	QueuedUpdaters.Empty();
	TArray<FNepUpdateEventTypeID> ArraysToRemove;
	
	for (auto& [TypeID, UpdaterArray] : UpdaterArrays)
	{
		UpdaterArray->ClearEvent();
		if (UpdaterArray->UpdaterIDs.IsEmpty()) { ArraysToRemove.Add(TypeID); }
	}
	
	for (const FNepUpdateEventTypeID& TypeID : ArraysToRemove)
	{
		UpdaterArrays.Remove(TypeID);
	}
}
