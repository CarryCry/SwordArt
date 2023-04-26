// Fill out your copyright notice in the Description page of Project Settings.


#include "UITest/StackStateMachineComponent.h"


void UStackStateMachineComponent::PushState(TScriptInterface<IStackStateInterface> NewState)
{
	//如果有状态
	if(StateCount()>0)
	{
		auto CurrentState = GetCurrentState();

		if (CurrentState != nullptr)
		{
			//退出当前状态Push表示被更高状态覆盖，但仍在栈中
			CurrentState->ExitState(Push);
		}

		CurrentStateTime = 0;

		//新状态入栈
		States.Push(NewState);

		UICount++;

		//调用新状态入栈状态且是Push进去的
		NewState->EnterState(Push);

		//调用入栈回调，告诉子类有新状态入栈
		StatePushed(NewState);
		
	}
}

void UStackStateMachineComponent::PopState()
{
	auto OriginState = GetCurrentState();

	if(OriginState != nullptr)
	{
		OriginState->ExitState(Pop);
	}

	CurrentStateTime = 0;

	States.Pop();

	UICount--;

	if(StateCount() > 0)
	{
		GetCurrentState()->EnterState(Pop);
	}

	StatePoped(OriginState);
	
}

void UStackStateMachineComponent::PopStates(int count)
{
	while(count>0)
	{
		PopState();
		count--;
	}
	
}

void UStackStateMachineComponent::PopAllStates()
{
	PopStates(StateCount());
}

void UStackStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(StateCount()>0 && GetCurrentState() != nullptr)
	{
		GetCurrentState()->UpdateState(DeltaTime);
	}
}

void UStackStateMachineComponent::EnterState(EStackAction StackAction)
{
	if(OnStateEnter.IsBound())
	{
		OnStateEnter.Broadcast();
	}

	//确保蓝图也能收到
	ReceiveEnterState(StackAction);
}

void UStackStateMachineComponent::ExitState(EStackAction StackAction)
{
	if(OnStateExit.IsBound())
	{
		OnStateExit.Broadcast();
	}

	ReceiveExitState(StackAction);
}

void UStackStateMachineComponent::UpdateState(float DeltaTime)
{
	ReceiveUpdateState(DeltaTime);
	CurrentStateTime += DeltaTime;

	if (StateCount()>0)
	{
		GetCurrentState()->UpdateState(DeltaTime);
	}
}

void UStackStateMachineComponent::StatePushed(TScriptInterface<IStackStateInterface> PushedState)
{
	//UE_LOG(LogStackStateMachine,Display,TEXT("Push状态：%s"),*PushedState.GetObject()->GetName());

	if(OnStatePushed.IsBound())
	{
		OnStatePushed.Broadcast(PushedState);
	}

	ReceiveStatePush(PushedState);
}

void UStackStateMachineComponent::StatePoped(TScriptInterface<IStackStateInterface> PopedState)
{
	//UE_LOG(LogStackStateMachine,Display,TEXT("Push状态：%s"),*PopedState.GetObject()->GetName());

	if(OnStatePoped.IsBound())
	{
		OnStatePoped.Broadcast(PopedState);
	}

	ReceiveStatePop(PopedState);
	
}




