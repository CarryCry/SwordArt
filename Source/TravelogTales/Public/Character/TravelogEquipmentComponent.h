// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/TravelogWeaponItem.h"
#include "TravelogEquipmentComponent.generated.h"




UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	Head        UMETA(DisplayName = "Head"),
	Chest       UMETA(DisplayName = "Chest"),
	Hands       UMETA(DisplayName = "Hands"),
	Legs        UMETA(DisplayName = "Legs"),
	Feet        UMETA(DisplayName = "Feet"),
	Waist       UMETA(DisplayName = "Waist"),
	Back        UMETA(DisplayName = "Back"),
	RightHand UMETA(DisplayName = "RightHand"),
	LeftHand UMETA(DisplayName = "LeftHand")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponEquipped, EEquipmentSlot, WeaponSlot, UTravelogWeaponItem*, WeaponItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponUnequipped, EEquipmentSlot, WeaponSlot);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELOGTALES_API UTravelogEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTravelogEquipmentComponent();

	UFUNCTION(BlueprintCallable, Category = "Equipment")
    bool EquipWeapon(EEquipmentSlot WeaponSlot, UTravelogWeaponItem* WeaponItem);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool UnequipWeapon(EEquipmentSlot WeaponSlot);

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnWeaponEquipped OnWeaponEquipped;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnWeaponUnequipped OnWeaponUnequipped;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<EEquipmentSlot, UTravelogWeaponItem*> EquippedWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<EEquipmentSlot, ATravelogWeaponBase*> EquippedWeaponActors;

private:
	EEquipmentSlot GetEquipmentSlotForWeapon(UTravelogWeaponItem* WeaponItem);


		
};
