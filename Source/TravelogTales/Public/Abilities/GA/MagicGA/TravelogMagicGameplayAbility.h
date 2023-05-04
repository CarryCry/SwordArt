// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/TravelogGameplayAbility.h"
#include "TravelogMagicGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UTravelogMagicGameplayAbility : public UTravelogGameplayAbility
{
	GENERATED_BODY()

public:
	// The spawn location for the projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	FVector SpawnLocation;

	// The spawn rotation for the projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	FRotator SpawnRotation;
	
	// Function to spawn the projectile
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile();

protected:
	// The projectile class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;
	
};
