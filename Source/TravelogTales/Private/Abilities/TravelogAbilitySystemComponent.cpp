// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TravelogAbilitySystemComponent.h"

#include "GameplayTagsModule.h"


bool UTravelogAbilitySystemComponent::GrantAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if (!Ability)
	{
		return false;
	}

	FGameplayAbilitySpec Spec(Ability, 1, INDEX_NONE, GetOwner());
	FGameplayAbilitySpecHandle SpecHandle = GiveAbility(Spec);

	return SpecHandle.IsValid();
}

bool UTravelogAbilitySystemComponent::RevokeAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if (!Ability)
	{
		return false;
	}

	FGameplayAbilitySpecHandle FoundHandle;

	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability->GetClass() == Ability)
		{
			FoundHandle = Spec.Handle;
			break;
		}
	}

	if (FoundHandle.IsValid())
	{
		ClearAbility(FoundHandle);
		return true;
	}

	return false;
}

bool UTravelogAbilitySystemComponent::HasAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if (!Ability)
	{
		return false;
	}

	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability->GetClass() == Ability)
		{
			return true;
		}
	}

	return false;
}

FActiveGameplayEffectHandle UTravelogAbilitySystemComponent::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> Effect,
	float Level)
{
	if (!Effect)
	{
		return FActiveGameplayEffectHandle();
	}

	UGameplayEffect* GameplayEffect = Effect.GetDefaultObject();
	FGameplayEffectSpec Spec(GameplayEffect, MakeEffectContext(), Level);

	return ApplyGameplayEffectSpecToSelf(Spec);
}

bool UTravelogAbilitySystemComponent::RemoveGameplayEffect(FActiveGameplayEffectHandle Handle)
{
	if (Handle.IsValid())
	{
		RemoveActiveGameplayEffect(Handle);
		return true;
	}

	return false;
}

void UTravelogAbilitySystemComponent::NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle,
	UGameplayAbility* Ability)
{
	UTravelogGameplayAbility* TravelogAbility = Cast<UTravelogGameplayAbility>(Ability);
	if (TravelogAbility)
	{
		float CooldownDuration = TravelogAbility->CooldownDuration;

		// 触发委托事件
		OnAbilityActivated.Broadcast(Ability, CooldownDuration);
	}
	
	Super::NotifyAbilityActivated(Handle, Ability);
}

/*
void UTravelogAbilitySystemComponent::ActivateAbilitiesWithTags(const FGameplayTagContainer& TagsToActivate,
	bool bActivate)
{
	
}

void UTravelogAbilitySystemComponent::ActivateAbilityWithTag(const FGameplayTag& TagToActivate, bool bActivate)
{
	FGameplayTagContainer TagsToActivate;
	TagsToActivate.AddTag(TagToActivate);
	ActivateAbilitiesWithTags(TagsToActivate, bActivate);
}
*/

