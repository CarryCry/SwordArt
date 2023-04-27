// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "TravelogAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UTravelogAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// 为这个ASC授予一个技能
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool GrantAbility(TSubclassOf<UGameplayAbility> Ability);

	// 从这个ASC撤销一个技能
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool RevokeAbility(TSubclassOf<UGameplayAbility> Ability);

	// 检查这个ASC是否具有某个技能
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool HasAbility(TSubclassOf<UGameplayAbility> Ability);

	// 应用游戏效果到这个ASC
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	FActiveGameplayEffectHandle ApplyGameplayEffect(TSubclassOf<UGameplayEffect> Effect, float Level);

	// 从这个ASC移除一个游戏效果
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool RemoveGameplayEffect(FActiveGameplayEffectHandle Handle);
/*
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbilitiesWithTags(const FGameplayTagContainer& TagsToActivate, bool bActivate);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbilityWithTag(const FGameplayTag& TagToActivate, bool bActivate);
*/

};
