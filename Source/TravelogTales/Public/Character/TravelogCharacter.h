// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "TravelogEquipmentComponent.h"
#include "TravelogInventoryComponent.h"
#include "Abilities/TravelogAbilitySystemComponent.h"
#include "Character/TravelogHealthyComponent.h"
#include "TravelogCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API ATravelogCharacter : public AALSCharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ATravelogCharacter(const FObjectInitializer& ObjectInitializer);
	
	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;




protected:
	UPROPERTY()
	UTravelogAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UTravelogHealthyComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	UTravelogEquipmentComponent* EquipmentComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UTravelogInventoryComponent* InventoryComponent;
	
	
	
};
