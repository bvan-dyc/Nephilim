#include "UI/Widget/NepContainerInventoryWidget.h"
#include "Interaction/Actor/NepInventoryInteractionProxy.h"
#include "Inventory/NepInventory.h"
#include "Inventory/ActorComponent/NepContainerInventoryComponent.h"
#include "Inventory/Resource/NepInventoryEvents.h"
#include "UI/Widget/NepItemSlotWidget.h"
#include "Components/WrapBox.h"
#include "Interaction/Component/NepInteractor.h"
#include "UI/NepUIEvents.h"
#include "UI/NepWidgetUpdater.h"
#include "UI/Widget/NepInventoryWidget.h"

void UNepContainerInventoryWidget::InitializeFromProxy(ANepInventoryInteractionProxy& Proxy)
{
    InteractionProxy = &Proxy;
    
    AActor* InteractableActor = Proxy.InteractableActor.Get();
    const UNepContainerInventoryComponent* ContainerComponent = InteractableActor ? InteractableActor->FindComponentByClass<UNepContainerInventoryComponent>() : nullptr;

    if (InventoryWidget)
    {
        InventoryWidget->SetInventory(ContainerComponent ? ContainerComponent->Inventory : nullptr);
    }
}

void UNepContainerInventoryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SetRenderOpacity(0.0f);
    
    WidgetUpdater = FNepWidgetUpdater::Create(GetWorld(), FSimpleDelegate::CreateUObject(this, &UNepContainerInventoryWidget::Update));
    if (WidgetUpdater)
    {
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_HideUI>();
        WidgetUpdater->ListenToUpdateEvent<FNepUIEvent_SetRightInventoryPanel>();
    }

    if (InventoryWidget)
    {
        InventoryWidget->OnItemClicked.BindUObject(this, &UNepContainerInventoryWidget::HandleItemClicked);
    }
}

void UNepContainerInventoryWidget::Update()
{
    if (!WidgetUpdater) { return; }
    
    const bool bHideUI = WidgetUpdater->GetUpdateEvent<FNepUIEvent_HideUI>() != nullptr;
    const TOptional<bool> ShowContainerInventory = [&]()->TOptional<bool>
    {
        if (const auto Event = WidgetUpdater->GetUpdateEvent<FNepUIEvent_SetRightInventoryPanel>())
        {
            return Event && Event->RightInventoryPanel == ENepRightInventoryPanel::Container;
        }
        return TOptional<bool>();
    }();
    
    if (bIsVisible && (bHideUI || (ShowContainerInventory && !*ShowContainerInventory)))
    {
        FadeOut();
    }
    else if (!bIsVisible && ShowContainerInventory && *ShowContainerInventory)
    {
        if (ANepInventoryInteractionProxy* Proxy = FNepInteractor::GetLocalProxy<ANepInventoryInteractionProxy>(this))
        {
            InitializeFromProxy(*Proxy);
            FadeIn();
        }
    }
}

void UNepContainerInventoryWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
    bIsVisible = true;
}

void UNepContainerInventoryWidget::FadeOut()
{
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
    bIsVisible = false;
}

void UNepContainerInventoryWidget::HandleItemClicked(const FNepItemID& ItemID) const
{
    if (FNepInventoryEvents* Events = FNepInventoryEvents::Get(this))
    {
        Events->ItemMoveCommandsOnClient.Emplace(ItemID, false);
    }
}
