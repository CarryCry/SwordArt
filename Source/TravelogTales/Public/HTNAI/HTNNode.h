// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HTNNode.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UHTNNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "HTN")
	TArray<UHTNNode*> Children;
};
