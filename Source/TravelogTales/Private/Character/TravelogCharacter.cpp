// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TravelogCharacter.h"


ATravelogCharacter::ATravelogCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UTravelogAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HealthComponent = CreateDefaultSubobject<UTravelogHealthyComponent>(TEXT("HealthComponent"));
	EquipmentComponent = CreateDefaultSubobject<UTravelogEquipmentComponent>(TEXT("EquipmentComponent"));
	InventoryComponent = CreateDefaultSubobject<UTravelogInventoryComponent>(TEXT("InventoryComponent"));
}

UAbilitySystemComponent* ATravelogCharacter::GetAbilitySystemComponent() const
{
	return  AbilitySystemComponent;
}

void ATravelogCharacter::BeginPlay()
{
	HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);
	Super::BeginPlay();
	
	
}


