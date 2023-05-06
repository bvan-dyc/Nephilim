#include "UI/Widget/NepPlayerInventoryWidget.h"
#include "GameFramework/Character.h"
#include "Interaction/Actor/NepInventoryInteractionProxy.h"
#include "Interaction/Component/NepInteractor.h"
#include "Inventory/NepInventory.h"
#include "Inventory/ActorComponent/NepEquipmentComponent.h"
#include "Inventory/Resource/NepInventoryEvents.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdater.h"
#include "UI/Widget/NepInventoryWidget.h"

void UNepPlayerInventoryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    SetRenderOpacity(0.0f);
    
    WidgetUpdater = FNepWidgetUpdater::Create(GetWorld(), FSimpleDelegate::CreateUObject(this, &UNepPlayerInventoryWidget::Update));
    if (WidgetUpdater)
    {
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_ShowUI>();
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_HideUI>();
    }
}

void UNepPlayerInventoryWidget::Update()
{
    if (!WidgetUpdater) { return; }

    if (WidgetUpdater->GetUpdateEvent<FNepUIEvent_ShowUI>() && !bIsVisible)
    {
        FadeIn();

        if (InventoryWidget)
        {
            UWorld* World = GetWorld();
            APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
            ACharacter* Character = PlayerController ? PlayerController->GetCharacter() : nullptr;
            UNepInventory* Inventory = Character ? UNepInventory::GetInventory(*Character) : nullptr;
            InventoryWidget->SetInventory(Inventory);
            InventoryWidget->OnItemClicked.BindUObject(this, &UNepPlayerInventoryWidget::HandleItemClicked);
        }
    }
    if (WidgetUpdater->GetUpdateEvent<FNepUIEvent_HideUI>() && bIsVisible)
    {
        FadeOut();
    }
}

void UNepPlayerInventoryWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
    bIsVisible = true;
}

void UNepPlayerInventoryWidget::FadeOut()
{
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
    bIsVisible = false;
}

void UNepPlayerInventoryWidget::HandleItemClicked(const FNepItemID& ItemID) const
{
    if (FNepInventoryEvents* Events = FNepInventoryEvents::Get(this))
    {
        if (FNepInteractor::GetLocalProxy<ANepInventoryInteractionProxy>(this))
        {
            Events->ItemMoveCommandsOnClient.Emplace(ItemID, true);
        }
        else
        {
            UWorld* World = GetWorld();
            APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
            ACharacter* Character = PlayerController ? PlayerController->GetCharacter() : nullptr;
            UNepEquipmentComponent* Equipment = Character ? Character->FindComponentByClass<UNepEquipmentComponent>() : nullptr;
            if (Equipment)
            {
                Equipment->Server_EquipItem(ItemID);
            }
        }
    }
}
