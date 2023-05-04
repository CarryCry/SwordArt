// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HTNOperator.h"
#include "HTNTask.h"
#include "HTNWorldState.h"
#include "UObject/NoExportTypes.h"
#include "HTNPlanner.generated.h"

UCLASS()
class TRAVELOGTALES_API UHTNTaskWrapper : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UHTNTask* Task;

	UPROPERTY()
	int32 Priority;

	UPROPERTY()
	float Weight;

	bool operator<(const UHTNTaskWrapper& Other) const;
};

/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELOGTALES_API UHTNPlanner : public UObject
{
	GENERATED_BODY()

public:
	// 在此定义规划器所需的成员变量和方法
	UPROPERTY()
	TArray<UHTNTask*> TaskList;

	UPROPERTY()
	TArray<UHTNNode*> NodeStack;

	UFUNCTION(BlueprintCallable)
	void Plan(UHTNWorldState* WorldState);

private:
	UHTNTaskWrapper* WrapTask(UHTNTask* Task, int32 Priority, float Weight);
	
	TArray<UHTNTaskWrapper*> WrapTasks(TArray<UHTNTask*> Tasks);
	
};
