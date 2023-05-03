// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "TravelogAbilitySystemComponent.h"
#include "Components/ActorComponent.h"
#include "CooldownManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELOGTALES_API UCooldownManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCooldownManagerComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
    void ApplyCooldownEffect(UGameplayAbility* ActivatedAbility, float CooldownDuration);

	UFUNCTION()
    void OnCooldownCompleted();
	
	UPROPERTY()
	UTravelogAbilitySystemComponent* AbilitySystemComponent; // 指向 AbilitySystemComponent 的指针

	UPROPERTY()
	TMap<TSubclassOf<UGameplayAbility>, FTimerHandle> ActiveCooldowns;


protected:
	

	
};
