// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HTNNode.h"
#include "HTNWorldState.h"
#include "UObject/NoExportTypes.h"
#include "HTNTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class TRAVELOGTALES_API UHTNTask : public UHTNNode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "HTN")
	void ExecuteTask(UHTNWorldState* WorldState);

	UPROPERTY(BlueprintReadWrite, Category = "HTN")
	float Priority;
	
	UPROPERTY(BlueprintReadWrite, Category = "HTN")
	float Weight;

	UFUNCTION(BlueprintNativeEvent, Category = "HTN")
    bool IsApplicable(UHTNWorldState* WorldState);

	UFUNCTION(BlueprintNativeEvent, Category = "HTN")
	TArray<UHTNTask*> DecomposeTask(UHTNWorldState* WorldState);

	
};
