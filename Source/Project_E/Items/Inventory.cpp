// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

void UInventory::AddItem(UItem* Item, bool bIsDuck)
{
    if (!Item)
		return;

    if (bIsDuck)
    {
        if (Item->Type == EItemType::Weapon)
            DuckWeaponInventory.Add(Item);
        else
            DuckNonWeaponInventory.Add(Item);
    }
    else
    {
        SetCatInventoryItem(Item);
    }

	UE_LOG(LogTemp, Warning, TEXT("Added item: %s"), *Item->Name);
}

void UInventory::RemoveItem(UItem* Item, bool bIsDuck)
{
    if (!Item)
        return;

    if (bIsDuck)
    {
        if (Item->Type == EItemType::Weapon)
            DuckWeaponInventory.Remove(Item);
        else
            DuckNonWeaponInventory.Remove(Item);
    }
    else
    {
        if (CatInventoryItem == Item)
            CatInventoryItem = nullptr;
    }

	UE_LOG(LogTemp, Warning, TEXT("Removed item: %s"), *Item->Name);
}

UItem* UInventory::RemoveLastItem(bool bIsDuck)
{
    UItem* RemovedItem = nullptr;

    if (DuckWeaponInventory.Num() > 0)
    {
        RemovedItem = DuckWeaponInventory.Pop();
    }

    return RemovedItem;
}

void UInventory::SetCatInventoryItem(UItem* Item)
{
    CatInventoryItem = Item;
}

UItem* UInventory::GetCatInventoryItem() const
{
    return CatInventoryItem;
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