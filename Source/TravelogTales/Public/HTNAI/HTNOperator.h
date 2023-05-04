// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HTNNode.h"
#include "HTNWorldState.h"
#include "UObject/NoExportTypes.h"
#include "HTNOperator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class TRAVELOGTALES_API UHTNOperator : public UHTNNode
{
	GENERATED_BODY()

public:
	// 定义操作符应用的接口，参数是当前世界状态
	UFUNCTION(BlueprintNativeEvent, Category = "HTN")
	void ApplyOperator(UHTNWorldState* WorldState);
	
};
