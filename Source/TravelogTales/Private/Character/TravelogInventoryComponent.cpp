// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TravelogInventoryComponent.h"


// Sets default values for this component's properties
UTravelogInventoryComponent::UTravelogInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

TSubclassOf<UTravelogItemBase> UTravelogInventoryComponent::GetItem(FPrimaryAssetId ItemId) const
{
	const FInventoryItem* StoredItem = InventoryItems.Find(ItemId);
	if (!StoredItem)
	{
		return nullptr;
	}

	return StoredItem->ItemClass;
}

void UTravelogInventoryComponent::SetItem(FPrimaryAssetId ItemId, TSubclassOf<UTravelogItemBase> ItemClass)
{
	if (!ItemClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTravelogInventoryComponent::SetItem - Invalid ItemClass"));
		return;
	}

	FInventoryItem& InventoryItem = InventoryItems.FindOrAdd(ItemId);
	InventoryItem.ItemClass = ItemClass;
}

void UTravelogInventoryComponent::AddItem(TSubclassOf<UTravelogItemBase> ItemClass, int32 Quantity)
{
	if (!ItemClass || Quantity <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTravelogInventoryComponent::AddItem - Invalid ItemClass or Quantity"));
		return;
	}

	UTravelogItemBase* Item = ItemClass.GetDefaultObject();
	FPrimaryAssetId ItemId = Item->GetPrimaryAssetId();

	FInventoryItem& InventoryItem = InventoryItems.FindOrAdd(ItemId);
	InventoryItem.ItemClass = ItemClass;
	InventoryItem.Quantity += Quantity;

	OnInventoryItemChanged.Broadcast(ItemClass, InventoryItem.Quantity);

}

void UTravelogInventoryComponent::RemoveItem(TSubclassOf<UTravelogItemBase> ItemClass, int32 Quantity)
{
	if (!ItemClass || Quantity <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTravelogInventoryComponent::RemoveItem - Invalid ItemClass or Quantity"));
		return;
	}

	int32 CurrentQuantity = GetItemQuantity(ItemClass);

	if (CurrentQuantity <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTravelogInventoryComponent::RemoveItem - Item not found in inventory"));
		return;
	}

	int32 NewQuantity = CurrentQuantity - Quantity;
    
	if (NewQuantity < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTravelogInventoryComponent::RemoveItem - Trying to remove more items than available"));
		return;
	}

	SetItemQuantity(ItemClass, NewQuantity);
	
}

int32 UTravelogInventoryComponent::GetItemQuantity(TSubclassOf<UTravelogItemBase> ItemClass) const
{
	if (!ItemClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTravelogInventoryComponent::GetItemQuantity - Invalid ItemClass"));
		return 0;
	}

	UTravelogItemBase* Item = ItemClass.GetDefaultObject();
	FPrimaryAssetId ItemId = Item->GetPrimaryAssetId();

	const FInventoryItem* StoredItem = InventoryItems.Find(ItemId);
	if (!StoredItem)
	{
		return 0;
	}

	// Now we can return the actual item quantity
	return StoredItem->Quantity;
}

void UTravelogInventoryComponent::SetItemQuantity(TSubclassOf<UTravelogItemBase> ItemClass, int32 Quantity)
{
	if (!ItemClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTravelogInventoryComponent::SetItemQuantity - Invalid ItemClass"));
		return;
	}

	if (Quantity < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTravelogInventoryComponent::SetItemQuantity - Invalid Quantity"));
		return;
	}

	FPrimaryAssetId AssetId = ItemClass->GetPrimaryAssetId();

	if (Quantity == 0)
	{
		// Remove the item from the inventory
		InventoryItems.Remove(AssetId);
	}
	else
	{
		// Update the item's quantity in the inventory
		FInventoryItem& Entry = InventoryItems.FindOrAdd(AssetId);
		Entry.ItemClass = ItemClass;
		Entry.Quantity = Quantity;
	}

	OnInventoryItemChanged.Broadcast(ItemClass, Quantity);
}

void UTravelogInventoryComponent::SaveInventory(FInventorySaveData& SaveData)
{
	SaveData.InventoryItems = InventoryItems;
}

void UTravelogInventoryComponent::LoadInventory(const FInventorySaveData& SaveData)
{
	InventoryItems = SaveData.InventoryItems;

	// Notify about the inventory update after loading
	for (const auto& ItemPair : InventoryItems)
	{
		TSubclassOf<UTravelogItemBase> ItemClass = GetItem(ItemPair.Key);
		OnInventoryItemChanged.Broadcast(ItemClass, ItemPair.Value.Quantity);
	}
}




