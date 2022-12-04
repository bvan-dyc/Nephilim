#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NepInteractionMenuWidget.generated.h"

UCLASS(Abstract)
class NEPHILIM_API UNepInteractionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UNepAnimatedWidgetSwitcherWidget* WidgetSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainEntryContainer;
	
	UPROPERTY(meta = (BindWidget))
	class UNepInteractionMenuEntryWidget* MainEntry;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* EntriesContainer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNepInteractionMenuEntryWidget> EntryClass;
	
	UPROPERTY(EditDefaultsOnly)
	float ListPadding = 10.0f;

	UPROPERTY()
	TArray<class UNepInteractionMenuEntryWidget*> Entries;

	// Currently unused
	int32 NumAvailableEntries = 0;

public:

	void SetEntries(const TArray<FText>& InteractionNames);

	void ShowMainEntry() const;
	void HideMainEntry() const;

	void ToggleMenu() const;
	void ExpandMenu() const;
	void CollapseMenu() const;

	bool IsExpanded() const;
	int32 GetNumAvailableEntries() const { return NumAvailableEntries; }

protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

};
