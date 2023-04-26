// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/TravelogPlayerController.h"

ATravelogPlayerController::ATravelogPlayerController()
{
	UIManager = CreateDefaultSubobject<UUIManagerComponent>(TEXT("UIManager"));
}

void ATravelogPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}
