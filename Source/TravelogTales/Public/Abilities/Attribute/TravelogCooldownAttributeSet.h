// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Attribute/TravelogAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TravelogCooldownAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UTravelogCooldownAttributeSet : public UTravelogAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Cooldown", ReplicatedUsing = OnRep_RemainingCooldown)
	FGameplayAttributeData RemainingCooldown;
	ATTRIBUTE_ACCESSORS(UTravelogCooldownAttributeSet, RemainingCooldown)

	UFUNCTION()
    void OnRep_RemainingCooldown(const FGameplayAttributeData& OldRemainingCooldown);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCooldownChanged, float, NewRemainingCooldown, float, OldRemainingCooldown);
	UPROPERTY(BlueprintAssignable, Category = "Cooldown")
	FOnCooldownChanged OnCooldownChanged;

	UFUNCTION(BlueprintCallable)
	void SetRemainingCooldown(float NewValue) ;

	UFUNCTION(BlueprintCallable)
    void ReduceRemainingCooldown(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void InitRemainingCooldown(float InitialValue) const;


protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;


	
};
