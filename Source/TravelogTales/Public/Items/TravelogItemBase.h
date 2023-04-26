// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TravelogItemBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UTravelogItemBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Information",meta=(DisplayName="道具类型"))
	FPrimaryAssetType ItemType;
	
};
