// Fill out your copyright notice in the Description page of Project Settings.


#include "UITest/StackState.h"

void UStackState::EnterState(EStackAction StackAction)
{
	//确保进入状态时调用蓝图版本进入的状态
	ReceiveEnterState(StackAction);
}

void UStackState::ExitState(EStackAction StackAction)
{
	//确保退出状态时调用蓝图版本进入的状态
	ReceiveExitState(StackAction);
}

void UStackState::UpdateState(float DeltaTime)
{
	//确保更新状态时调用蓝图版本进入的状态
	ReceiveUpdateState(DeltaTime);
}


