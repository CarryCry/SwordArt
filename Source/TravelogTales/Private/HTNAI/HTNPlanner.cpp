// Fill out your copyright notice in the Description page of Project Settings.


#include "HTNAI/HTNPlanner.h"

bool UHTNTaskWrapper::operator<(const UHTNTaskWrapper& Other) const
{
	if (Priority != Other.Priority)
	{
		return Priority < Other.Priority;
	}
	else
	{
		return Weight < Other.Weight;
	}
}

void UHTNPlanner::Plan(UHTNWorldState* WorldState)
{
	TArray<UHTNTaskWrapper*> TaskStack = WrapTasks(TaskList);
	TaskStack.Sort();

	TArray<UHTNTask*> TaskSequence;
	while (TaskStack.Num() > 0)
	{
		UHTNTaskWrapper* CurrentWrapper = TaskStack.Pop();
		UHTNTask* CurrentTask = CurrentWrapper->Task;

		if (CurrentTask->IsApplicable(WorldState))
		{
			TaskSequence.Add(CurrentTask);
			CurrentTask->ExecuteTask(WorldState);
		}
		else
		{
			TArray<UHTNTask*> Subtasks = CurrentTask->DecomposeTask(WorldState);
			TArray<UHTNTaskWrapper*> WrappedSubtasks = WrapTasks(Subtasks);
			TaskStack.Append(WrappedSubtasks);
			TaskStack.Sort();
		}
	}
}

UHTNTaskWrapper* UHTNPlanner::WrapTask(UHTNTask* Task, int32 Priority, float Weight)
{
	UHTNTaskWrapper* TaskWrapper = NewObject<UHTNTaskWrapper>();
	TaskWrapper->Task = Task;
	TaskWrapper->Priority = Priority;
	TaskWrapper->Weight = Weight;
	return TaskWrapper;
}

TArray<UHTNTaskWrapper*> UHTNPlanner::WrapTasks(TArray<UHTNTask*> Tasks)
{
	TArray<UHTNTaskWrapper*> WrappedTasks;
	for (UHTNTask* Task : Tasks)
	{
		WrappedTasks.Add(WrapTask(Task, Task->Priority, Task->Weight));
	}
	return WrappedTasks;
}


