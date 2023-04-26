// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Attribute/TravelogHealthAttributeSet.h"

UTravelogHealthAttributeSet::UTravelogHealthAttributeSet()
{
}

void UTravelogHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		// Clamp Health between 0 and MaxHealth.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		// Ensure MaxHealth is always positive.
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}
