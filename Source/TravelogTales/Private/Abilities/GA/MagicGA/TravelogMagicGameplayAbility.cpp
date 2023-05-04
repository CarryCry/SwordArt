// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA/MagicGA/TravelogMagicGameplayAbility.h"

void UTravelogMagicGameplayAbility::SpawnProjectile()
{
	if (ProjectileClass)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// Spawn the projectile at the specified location and rotation
			AActor* SpawnedProjectile = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParameters);
			
		}
	}
}
