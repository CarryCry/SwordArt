// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TravelogHealthyComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "UI/UIManager.h"

// Sets default values for this component's properties
UTravelogHealthyComponent::UTravelogHealthyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	HealthAttributeSet = CreateDefaultSubobject<UTravelogHealthAttributeSet>(TEXT("HealthAttributeSet"));

	// ...
}




void UTravelogHealthyComponent::InitializeWithAbilitySystem(UTravelogAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		return;
	}

	HealthAttributeSet = NewObject<UTravelogHealthAttributeSet>(InASC);
	
	if (!HealthAttributeSet)
	{
		return;
	}

	// Register to listen for attribute changes.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UTravelogHealthAttributeSet::GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UTravelogHealthAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);

	AbilitySystemComponent->AddAttributeSetSubobject(HealthAttributeSet);
}


float UTravelogHealthyComponent::GetHealth() const
{
	if (HealthAttributeSet)
	{
		return HealthAttributeSet->GetHealth();
	}

	return 0.0f;
}

float UTravelogHealthyComponent::GetMaxHealth() const
{
	if (HealthAttributeSet)
	{
		return HealthAttributeSet->GetMaxHealth();
	}

	return 0.0f;
}

float UTravelogHealthyComponent::GetHealthNormalized() const
{
	float Health = GetHealth();
	float MaxHealth = GetMaxHealth();

	if (MaxHealth > 0)
	{
		return Health / MaxHealth;
	}

	return 0.0f;
}

static AActor* GetInstigatorFromAttrChangeData(const FOnAttributeChangeData& ChangeData)
{
	if (ChangeData.GEModData != nullptr)
	{
		const FGameplayEffectContextHandle& EffectContext = ChangeData.GEModData->EffectSpec.GetEffectContext();
		return EffectContext.GetOriginalInstigator();
	}

	return nullptr;
}

void UTravelogHealthyComponent::HandleHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	OnHealthChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeData(ChangeData));
}

void UTravelogHealthyComponent::HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	OnMaxHealthChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeData(ChangeData));
}

void UTravelogHealthyComponent::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude)
{
}


