// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/TravelogWeaponItem.h"
#include "TravelogInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, TSubclassOf<UTravelogItemBase>, ItemClass, int32, NewQuantity);

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UTravelogItemBase> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 Quantity;
};

USTRUCT(BlueprintType)
struct FInventorySaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "SaveData")
	TMap<FPrimaryAssetId, FInventoryItem> InventoryItems;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELOGTALES_API UTravelogInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/*Getter SetterBegin*/
	UTravelogInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
    TSubclassOf<UTravelogItemBase> GetItem(FPrimaryAssetId ItemId) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItem(FPrimaryAssetId ItemId, TSubclassOf<UTravelogItemBase> ItemClass);
	/*Getter SetterEnd*/

	UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(TSubclassOf<UTravelogItemBase> ItemClass, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(TSubclassOf<UTravelogItemBase> ItemClass, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetItemQuantity(TSubclassOf<UTravelogItemBase> ItemClass) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetItemQuantity(TSubclassOf<UTravelogItemBase> ItemClass, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SaveInventory(FInventorySaveData& SaveData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadInventory(const FInventorySaveData& SaveData);


	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnInventoryItemChanged;



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<FPrimaryAssetId, FInventoryItem> InventoryItems;


	
};
