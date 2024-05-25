// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

void UInventory::AddItem(UItem* Item)
{
    if (!Item)
		return;

    if (Item->Type == EItemType::Weapon)
    {
        WeaponInventory.Add(Item);
    }
    else if (Item->Type == EItemType::NonWeapon)
    {
        NonWeaponInventory.Add(Item);
    }

	UE_LOG(LogTemp, Warning, TEXT("Added item: %s"), *Item->Name);
}

void UInventory::RemoveItem(UItem* Item)
{
    if (!Item)
        return;

    if (Item->Type == EItemType::Weapon)
    {
        WeaponInventory.Remove(Item);
    }
    else if (Item->Type == EItemType::NonWeapon)
    {
        NonWeaponInventory.Remove(Item);
    }

	UE_LOG(LogTemp, Warning, TEXT("Removed item: %s"), *Item->Name);
}

UItem* UInventory::RemoveLastItem()
{
    UItem* RemovedItem = nullptr;

    if (WeaponInventory.Num() > 0)
    {
        RemovedItem = WeaponInventory.Pop();
    }

    return RemovedItem;
}

/*
bool UInventory::IsFull() const
{
	const int32 MaxCapacity = 9;
	int32 NumItems = Items.Num();

	if (NumItems >= MaxCapacity)
		return true;

	return false;
}
*/