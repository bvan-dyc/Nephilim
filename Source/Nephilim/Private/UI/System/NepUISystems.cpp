#include "UI/System/NepUISystems.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdateManager.h"
#include "UI/DataAsset/NepUIGlobalsDataAsset.h"
#include "UI/Widget/NepHUDWidget.h"

void FNepUISystems::InitializeGlobals(FArcRes<FArcCoreData> CoreData, FArcRes<FNepUIGlobals> UIGlobals)
{
	TArray<UObject*> Assets;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Globals"), Assets, EngineUtils::ATL_Regular);
	for (auto Asset : Assets)
	{
		if (UNepUIGlobalsDataAsset* UIGlobalsDataAsset = Cast<UNepUIGlobalsDataAsset>(Asset))
		{
			*UIGlobals = UIGlobalsDataAsset->UIGlobals;
		}
	}
}

void FNepUISystems::CreateHUD(FArcRes<FArcCoreData> CoreData, FArcRes<FNepUIGlobals> UIGlobals, FArcRes<FNepWidgetData> WidgetData)
{
	if (UIGlobals->HUDWidget)
	{
		UNepHUDWidget* HUDWidget = CreateWidget<UNepHUDWidget>(CoreData->World.Get(), UIGlobals->HUDWidget);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
			WidgetData->HUDWidget = HUDWidget;
		}
	}
}

void FNepUISystems::UpdateWidgets(FArcRes<FNepWidgetData> WidgetData)
{
	WidgetData->WidgetUpdateManager->NotifyQueuedUpdaters();
	WidgetData->WidgetUpdateManager->ClearQueuedUpdatersAndEvents();
}

void FNepUISystems::HandleToggleUI(FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepCharacterEvents> Events)
{
	if (!Events->bToggleUI) { return; }
	Events->SetUIVisibilityCommand = !WidgetData->bUIVisible;
	if (!WidgetData->bUIVisible)
	{
		WidgetData->WidgetUpdateManager->TriggerWidgetUpdateEvent(FNepUIEvent_ShowUI());
		WidgetData->WidgetUpdateManager->TriggerWidgetUpdateEvent(FNepUIEvent_SetRightInventoryPanel { ENepRightInventoryPanel::Equipment });
	}
	else
	{
		WidgetData->WidgetUpdateManager->TriggerWidgetUpdateEvent(FNepUIEvent_HideUI());
	}
}

void FNepUISystems::SetUIVisibility(FArcRes<FArcCoreData> CoreData, FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepCharacterEvents> Events)
{
	if (!Events->SetUIVisibilityCommand) { return; }
	WidgetData->bUIVisible = *Events->SetUIVisibilityCommand;

	UWorld* World = CoreData->World.Get();
	APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(WidgetData->bUIVisible);
		if (WidgetData->bUIVisible)
		{
			PlayerController->SetInputMode(FInputModeGameAndUI());
		}
		else
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
}
