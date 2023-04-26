// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Attribute/TravelogAttributeSet.h"
#include "TravelogHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UTravelogHealthAttributeSet : public UTravelogAttributeSet
{
	GENERATED_BODY()

public:
	UTravelogHealthAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTravelogHealthAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTravelogHealthAttributeSet, MaxHealth)

	// Override PreAttributeChange to enforce constraints on Health and MaxHealth.
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;


private:
	// Incoming healing. This is mapped directly to +Health
	UPROPERTY(BlueprintReadOnly, Category="Health", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Healing;

	// Incoming damage. This is mapped directly to -Health
	UPROPERTY(BlueprintReadOnly, Category="Health", Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;
	
};
