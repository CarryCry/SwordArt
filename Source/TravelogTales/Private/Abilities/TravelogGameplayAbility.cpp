// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TravelogGameplayAbility.h"
#include "Abilities/Attribute/TravelogCooldownAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Abilities/CooldownManagerComponent.h"


bool UTravelogGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                                  const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	
	
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (ActorInfo->AbilitySystemComponent.IsValid())
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		AActor* OwnerActor = ASC->GetOwner();

		if (OwnerActor)
		{
			UCooldownManagerComponent* CooldownManager = OwnerActor->FindComponentByClass<UCooldownManagerComponent>();

			if (CooldownManager)
			{
				FTimerHandle* TimerHandlePtr = CooldownManager->ActiveCooldowns.Find(GetClass());

				if (ActorInfo && ActorInfo->OwnerActor.IsValid() && TimerHandlePtr)
				{
					UWorld* World = ActorInfo->OwnerActor->GetWorld();
					if (World)
					{
						if (World->GetTimerManager().IsTimerActive(*TimerHandlePtr))
						{
							// 技能处于冷却状态，不能激活
							return false;
						}
					}
				}
			}
		}
	}
	
	return true;
}
