// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UILayerEnum.generated.h"

UENUM(BlueprintType)
enum class EUILayer : uint8
{
	Background,
	MainMenu,
	PopUp,
	Tooltip
};

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UUILayerEnum : public UObject
{
	GENERATED_BODY()
	
};
