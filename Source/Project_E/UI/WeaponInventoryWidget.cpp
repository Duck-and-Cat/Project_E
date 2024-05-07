// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInventoryWidget.h"
#include "SlotWidget.h"
#include "../Items/Inventory.h"

void UWeaponInventoryWidget::UpdateInventory(const TArray<class UItem*>& Items)
{
	UInventory* Inventory = NewObject<UInventory>();
	TArray<UItem*>& WeaponItems = Inventory->WeaponInventory;

	Super::UpdateInventory(WeaponItems);

    /*
    // �� ������ �߰��Ͽ� ��ĭ 6���� �����մϴ�.
    const int32 MaxSlots = 6;
    const int32 NumEmptySlots = MaxSlots - Items.Num();
    for (int32 i = 0; i < NumEmptySlots; ++i)
    {
        USlotWidget* NewEmptySlot = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass);
        if (NewEmptySlot)
        {
            NewEmptySlot->UpdateSlot(nullptr); // �� ������ ������Ʈ�մϴ�.
            InventoryPanel->AddChild(NewEmptySlot); // ������ �κ��丮 �гο� �߰��մϴ�.
        }
    }*/
}
