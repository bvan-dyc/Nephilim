#include "UI/Widget/NepHUDWidget.h"
#include "ArcECSSubsystem.h"
#include "Resource/ArcCoreData.h"
#include "Character/Component/NepCharacterData.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Resource/NepUIGlobals.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/GameViewportClient.h"
#include "Engine/UserInterfaceSettings.h"
#include "Interaction/Resource/NepCurrentInteractableData.h"

void UNepHUDWidget::UpdateInteractableIndicator()
{
    UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(this);
    FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
    FNepCurrentInteractableData* CurrentInteractableData = Universe ? Universe->GetResource<FNepCurrentInteractableData>() : nullptr;
    if (!CurrentInteractableData || !Canvas) { return; }

    if (FocusedInteractable == CurrentInteractableData->FocusedInteractable)
    {
        UWorld* World = GetWorld();
        APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
        FArcCoreData* CoreData = Universe->GetResource<FArcCoreData>();
        TWeakObjectPtr<AActor>* InteractableActorPtr = CoreData ? CoreData->ActorsByEntity.Find(FocusedInteractable) : nullptr;
        AActor* InteractableActor = InteractableActorPtr ? InteractableActorPtr->Get() : nullptr;
        UCanvasPanelSlot* IndicatorSlot = FocusedInteractableWidget ? Cast<UCanvasPanelSlot>(FocusedInteractableWidget->Slot) : nullptr;
        
        const TOptional<float> DPIScale = [&]()->TOptional<float>
        {
            UGameViewportClient* Viewport = World ? World->GetGameViewport() : nullptr;
            if (!Viewport) { return {}; }
            FVector2D ViewportSize;
            Viewport->GetViewportSize(ViewportSize);
            const float scale = GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(FIntPoint(ViewportSize.X, ViewportSize.Y));
            return scale > 0.0f ? scale : 1.0f;
        }();
        
        if (PlayerController && InteractableActor && IndicatorSlot && DPIScale)
        {
            const FVector InteractableLocation = [&]()
            {
                FVector Origin;
                FVector Extents;
                InteractableActor->GetActorBounds(true, Origin, Extents);
                FVector Result = InteractableActor->GetActorLocation();
                Result.Z = Origin.Z + Extents.Z + 10.0f;
                return Result;
            }();
            FVector2D WidgetLocation;
            UGameplayStatics::ProjectWorldToScreen(PlayerController, InteractableLocation, WidgetLocation);
            IndicatorSlot->SetPosition(WidgetLocation / *DPIScale);
        }
    }
    else
    {
        if (FocusedInteractableWidget)
        {
            FocusedInteractableWidget->RemoveFromParent();
            FocusedInteractableWidget = nullptr;
        }
        
        FocusedInteractable = CurrentInteractableData->FocusedInteractable;
        if (Universe->IsValid(FocusedInteractable))
        {
            FNepUIGlobals* UIGlobals = Universe->GetResource<FNepUIGlobals>();
            if (UIGlobals)
            {
                const bool bIsCharacter = Universe->HasComponent<FNepCharacterData>(FocusedInteractable);
                TSubclassOf<UUserWidget> Class = bIsCharacter ? UIGlobals->CharacterInteractionIndicatorWidget : UIGlobals->MinimalInteractionIndicatorWidget;
                if (Class)
                {
                    FocusedInteractableWidget = CreateWidget<UUserWidget>(this, Class);
                    if (UCanvasPanelSlot* IndicatorSlot = Canvas->AddChildToCanvas(FocusedInteractableWidget))
                    {
                        IndicatorSlot->SetAutoSize(true);
                        IndicatorSlot->SetAlignment(FVector2D(0.5f, 1.0f));
                    }
                }
            }
        }
    }
}
