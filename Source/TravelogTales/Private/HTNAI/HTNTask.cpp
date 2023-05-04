// Fill out your copyright notice in the Description page of Project Settings.


#include "HTNAI/HTNTask.h"

void UHTNTask::ExecuteTask_Implementation(UHTNWorldState* WorldState)
{
}

bool UHTNTask::IsApplicable_Implementation(UHTNWorldState* WorldState)
{
	return true;
}

TArray<UHTNTask*> UHTNTask::DecomposeTask_Implementation(UHTNWorldState* WorldState)
{
	return TArray<UHTNTask*>(); 
}
