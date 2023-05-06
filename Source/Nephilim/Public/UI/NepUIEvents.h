#pragma once

struct FNepUIEvent_ShowUI {};
struct FNepUIEvent_HideUI {};

enum class ENepRightInventoryPanel : uint8
{
	Equipment,
	Container
};

struct FNepUIEvent_SetRightInventoryPanel
{
	ENepRightInventoryPanel RightInventoryPanel = ENepRightInventoryPanel::Equipment;
};

struct FNepUIEvent_InventoryChanged {};

struct FNepUIEvent_UpdateEquipment
{
	TWeakObjectPtr<class UNepEquipmentComponent> Equipment;
};
