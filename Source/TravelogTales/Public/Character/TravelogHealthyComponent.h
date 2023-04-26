// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/TravelogAbilitySystemComponent.h"
#include "Abilities/Attribute/TravelogHealthAttributeSet.h"
#include "Components/ActorComponent.h"
#include "TravelogHealthyComponent.generated.h"

class UTravelogHealthyComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, UTravelogHealthyComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELOGTALES_API UTravelogHealthyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTravelogHealthyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Health")
	void InitializeWithAbilitySystem(UTravelogAbilitySystemComponent* InASC);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthNormalized() const;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnMaxHealthChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	UTravelogHealthAttributeSet* HealthAttributeSet;

protected:
	virtual void HandleHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);

	UPROPERTY()
	UTravelogAbilitySystemComponent* AbilitySystemComponent;





	
};
