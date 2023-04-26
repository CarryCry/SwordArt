// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSPlayerController.h"
#include "UITest/UIManagerComponent.h"
#include "TravelogPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API ATravelogPlayerController : public AALSPlayerController
{
	GENERATED_BODY()

	ATravelogPlayerController();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "UIManager")
	UUIManagerComponent* UIManager;

	virtual void BeginPlay() override;
	
};
