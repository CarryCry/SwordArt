// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffectExtension.h"
#include "TravelogAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)



UCLASS()
class TRAVELOGTALES_API UTravelogAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UTravelogAttributeSet();

	template<typename AttributeSetType>
	float GetAttributeValue(const FGameplayAttribute& Attribute) const
	{
		return GetNumericAttribute(Attribute);
	}
	
};
