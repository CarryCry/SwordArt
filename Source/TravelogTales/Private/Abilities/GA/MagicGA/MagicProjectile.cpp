// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA/MagicGA/MagicProjectile.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MagicParticleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MagicParticleComponent"));
	MagicParticleComponent->SetupAttachment(RootComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));


}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetActor)
	{
		FVector DirectionToTarget = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector CurrentDirection = GetActorForwardVector();
		FVector NewDirection = FMath::Lerp(CurrentDirection, DirectionToTarget, TrackingStrength * DeltaTime);
		NewDirection.Normalize();

		SetActorLocation(GetActorLocation() + NewDirection * ProjectileSpeed * DeltaTime);
		SetActorRotation(NewDirection.Rotation());
	}
	else
	{
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * ProjectileSpeed * DeltaTime);
	}

}

