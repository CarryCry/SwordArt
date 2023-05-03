// Fill out your copyright notice in the Description page of Project Settings.

/*这个类暂时没用*/

#include "Abilities/CooldownManagerComponent.h"

UCooldownManagerComponent::UCooldownManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCooldownManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		AbilitySystemComponent = Owner->FindComponentByClass<UTravelogAbilitySystemComponent>();
		if (AbilitySystemComponent)
		{
			// 订阅 OnAbilityActivated 委托
			AbilitySystemComponent->OnAbilityActivated.AddDynamic(this, &UCooldownManagerComponent::ApplyCooldownEffect);
		}
	}
}

void UCooldownManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	 AActor* Owner = GetOwner();
        if (Owner)
        {
            AbilitySystemComponent = Owner->FindComponentByClass<UTravelogAbilitySystemComponent>();
            if (AbilitySystemComponent)
            {
                // 订阅 OnAbilityActivated 委托
                AbilitySystemComponent->OnAbilityActivated.AddDynamic(this, &UCooldownManagerComponent::ApplyCooldownEffect);
            }
        }
}


void UCooldownManagerComponent::ApplyCooldownEffect(UGameplayAbility* ActivatedAbility, float CooldownDuration)
{
	if (ActivatedAbility == nullptr)
	{
		return;
	}

	FTimerHandle CooldownTimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("OnCooldownCompleted"));
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, TimerDelegate, CooldownDuration, false);


	ActiveCooldowns.Add(ActivatedAbility->GetClass(), CooldownTimerHandle);
}


void UCooldownManagerComponent::OnCooldownCompleted()
{
	for (auto& Elem : ActiveCooldowns)
	{
		FTimerHandle Handle = Elem.Value;
		if (!GetWorld()->GetTimerManager().IsTimerActive(Handle))
		{
			ActiveCooldowns.Remove(Elem.Key);
			break;
		}
	}
}







