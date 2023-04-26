// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TravelogWeaponBase.h"

// Sets default values
ATravelogWeaponBase::ATravelogWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

}




