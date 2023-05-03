// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Attribute/TravelogCooldownAttributeSet.h"
#include "TravelogGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UTravelogGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Travelog")
	float CooldownDuration;


	virtual auto CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                                const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	                                FGameplayTagContainer* OptionalRelevantTags) const -> bool override;

	


protected:

	
};
