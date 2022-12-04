#include "UI/Widget/NepInteractionMenuWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "UI/Widget/NepInteractionMenuEntryWidget.h"
#include "UI/Resource/NepWidgetData.h"
#include "UI/Widget/NepAnimatedWidgetSwitcherWidget.h"

void UNepInteractionMenuWidget::SetEntries(const TArray<FText>& InteractionNames)
{
    if (InteractionNames.Num() <= 1)
    {
        CollapseMenu();
    }
    
    if (MainEntry && InteractionNames.Num() > 0)
    {
        MainEntry->SetInteractionName(
            InteractionNames.Num() == 1 ?
            InteractionNames[0] :
            NSLOCTEXT("Interaction", "InteractionExpandMenu", "Interact...")
        );
    }
    
    if (!EntriesContainer) { return; }

    NumAvailableEntries = InteractionNames.Num();
    
    for (int32 i = 0; i < InteractionNames.Num(); ++i)
    {
        UNepInteractionMenuEntryWidget* Entry = [&]
        {
            const bool bIsValidIndex = Entries.IsValidIndex(i);
            if (bIsValidIndex && Entries[i]) { return Entries[i]; }
            UNepInteractionMenuEntryWidget* NewEntry = CreateWidget<UNepInteractionMenuEntryWidget>(this, EntryClass);
            if (bIsValidIndex)
            {
                Entries[i] = NewEntry;
            }
            else
            {
                Entries.Add(NewEntry);
                if (UVerticalBoxSlot* EntrySlot = EntriesContainer->AddChildToVerticalBox(NewEntry))
                {
                    EntrySlot->SetPadding(i == 0 ? FMargin(0.0f) : FMargin(0.0f, ListPadding, 0.0f, 0.0f));
                }
            }
            return NewEntry;
        }();
        
        if (Entry)
        {
            Entry->SetInteractionNameAndHotkeyIndex(InteractionNames[i], i);
            Entry->SetVisibility(ESlateVisibility::HitTestInvisible);
        }
    }
    for (int32 i = InteractionNames.Num(); i < Entries.Num(); ++i)
    {
        if (Entries[i])
        {
            Entries[i]->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void UNepInteractionMenuWidget::ShowMainEntry() const
{
    if (MainEntryContainer)
    {
        MainEntryContainer->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
}

void UNepInteractionMenuWidget::HideMainEntry() const
{
    if (MainEntryContainer)
    {
        MainEntryContainer->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UNepInteractionMenuWidget::ToggleMenu() const
{
    if (WidgetSwitcher)
    {
        const int32 CurrentIndex = WidgetSwitcher->GetActiveWidgetIndex();
        WidgetSwitcher->SetActiveWidgetIndex((CurrentIndex + 1) % 2);
    }
}

void UNepInteractionMenuWidget::ExpandMenu() const
{
    if (WidgetSwitcher)
    {
        WidgetSwitcher->SetActiveWidgetIndex(1);
    }
}

void UNepInteractionMenuWidget::CollapseMenu() const
{
    if (WidgetSwitcher)
    {
        WidgetSwitcher->SetActiveWidgetIndex(0);
    }
}

bool UNepInteractionMenuWidget::IsExpanded() const
{
    return WidgetSwitcher && WidgetSwitcher->GetActiveWidgetIndex() == 1;
}

void UNepInteractionMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (EntriesContainer)
    {
        EntriesContainer->ClearChildren();
    }
}

void UNepInteractionMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (FNepWidgetData* WidgetData = FNepWidgetData::Get(this))
    {
        WidgetData->InteractionMenuWidget = this;
    }
}
