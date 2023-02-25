#include "UI/System/NepUISystems.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "UI/DataAsset/NepUIGlobalsDataAsset.h"
#include "UI/Widget/NepContainerInventoryWidget.h"
#include "UI/Widget/NepEquipmentWidget.h"
#include "UI/Widget/NepHUDWidget.h"
#include "UI/Widget/NepInventoryWidget.h"
#include "UI/Widget/NepTopBarWidget.h"
#include "UI/Widget/Dialogue/NepConversationWidget.h"

void FNepUISystems::InitializeUI(FArcRes<FArcCoreData> CoreData, FArcRes<FNepUIGlobals> UIGlobals, FArcRes<FNepWidgetData> WidgetData)
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

void FNepUISystems::HandleToggleUI(FArcRes<FNepWidgetData> WidgetData, FArcRes<FNepCharacterEvents> Events)
{
	if (!Events->bToggleUI) { return; }
	Events->SetUIVisibilityCommand = !WidgetData->bUIVisible;
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
	
	UNepTopBarWidget* TopBar = WidgetData->TopBarWidget.Get();
	UNepInventoryWidget* Inventory = WidgetData->InventoryWidget.Get();
	UNepEquipmentWidget* Equipment = WidgetData->EquipmentWidget.Get();
	UNepContainerInventoryWidget* Container = WidgetData->ContainerInventoryWidget.Get();
	UNepConversationWidget* ConversationPanel = WidgetData->ConversationWidget.Get();
	UNepCutsceneConversationWidget* CutscenePanel = WidgetData->CutsceneConversationWidget.Get();
	
	if (TopBar && Inventory && Equipment && Container)
	{
		if (WidgetData->bUIVisible)
		{
			TopBar->FadeIn();
			Inventory->FadeIn();
			if (Events->bShowContainer)
			{
				Container->FadeIn();
			}
			else
			{
				Equipment->FadeIn();
			}
		}
		else
		{
			TopBar->FadeOut();
			Inventory->FadeOut();
			Equipment->FadeOut();
			Container->FadeOut();
		}
	}
}
