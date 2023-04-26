// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "UILayerEnum.h"
#include "TravelogUI.generated.h"


/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class TRAVELOGTALES_API UTravelogUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") 
	FGameplayTag UITag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Layer")
	EUILayer UILayer = EUILayer::MainMenu;

	UFUNCTION(BlueprintNativeEvent, Category = "UI Events")
    void OnGameEvent(FGameplayTag EventTag);
	
};
