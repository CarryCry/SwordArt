// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StackStateInterface.h"
#include "Components/ActorComponent.h"
#include "StackStateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStackStatePushPopSignature,TScriptInterface<IStackStateInterface>,State);

UCLASS(Blueprintable,BlueprintType,meta=(BlueprintSpawnableComponent,ShortTooltip = "A StackStateMachineComponent"))
class TRAVELOGTALES_API UStackStateMachineComponent : public UActorComponent,public  IStackStateInterface
{
	GENERATED_BODY()

public:
	/*压入一个新状态到栈中*/
	UFUNCTION(BlueprintCallable,Category="StackStateMachine")
	void PushState(TScriptInterface<IStackStateInterface> NewState);

	/*弹出当前状态*/
	UFUNCTION(BlueprintCallable,Category="StackStateMachine")
	void PopState();

	/*弹出多个状态*/
	UFUNCTION(BlueprintCallable,Category="StackStateMachine")
	void PopStates(int count);

	/*弹出所有状态*/
	UFUNCTION(BlueprintCallable,Category="StackStateMachine")
	void PopAllStates();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*IStackStateInterface Begin*/
	virtual  void EnterState(EStackAction StackAction) override;
	virtual  void ExitState(EStackAction StackAction) override;

	/*更新当前状态Tick中调用*/
	virtual  void UpdateState(float DeltaTime) override;
	/*IStackStateInterface End*/

	/*蓝图回调开始*/
	UFUNCTION(BlueprintImplementableEvent,Category= "StackState",meta=(DisPlayName = "OnEnterState" ))
	void ReceiveEnterState(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent,Category= "StackState",meta=(DisPlayName = "OnExitState" ))
	void ReceiveExitState(EStackAction StackAction);
	
	UFUNCTION(BlueprintImplementableEvent,Category= "StackState",meta=(DisPlayName = "OnUpdateState" ))
	void ReceiveUpdateState(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent,Category= "StackState",meta=(DisPlayName = "StatePush" ))
	void ReceiveStatePush(const TScriptInterface<IStackStateInterface>& PushState);

	UFUNCTION(BlueprintImplementableEvent,Category= "StackState",meta=(DisPlayName = "StatePop" ))
	void ReceiveStatePop(const TScriptInterface<IStackStateInterface>& PopState);
	/*蓝图回调结束*/

	/*作为子状态机时，当进入状态时执行此事件*/
	UPROPERTY(BlueprintAssignable,Category="StackStateMachine")
	FOnStateEnterSignature OnStateEnter;

	/*退出时执行此事件*/
	UPROPERTY(BlueprintAssignable,Category="StackStateMachine")
	FOnStateExitSignature OnStateExit;

	UPROPERTY(BlueprintAssignable,Category="StackStateMachine")
	FOnStackStatePushPopSignature OnStatePushed;

	UPROPERTY(BlueprintAssignable,Category="StackStateMachine")
	FOnStackStatePushPopSignature OnStatePoped;

	/*Getter SetterBegin*/
	UFUNCTION(BlueprintPure,Category="StackStateMachine")
	TScriptInterface<IStackStateInterface> GetCurrentState(){return States[StateCount()-1];}

	UFUNCTION(BlueprintPure,Category="StackStateMachine")
	TScriptInterface<IStackStateInterface> GetUnderState(){return States[StateCount()-2];}

	TScriptInterface<IStackStateInterface> GetState(int32 Index){return  States[Index];}

	UFUNCTION(BlueprintPure,Category="StackStateMachine")
	int32 StateCount(){return States.Num();}

	UFUNCTION(BlueprintPure,Category="StackStateMachine")
	FORCEINLINE float GetCurrentStateTime()const {return  CurrentStateTime;}

	



protected:
	virtual void StatePushed(TScriptInterface<IStackStateInterface> PushedState);
	virtual void StatePoped(TScriptInterface<IStackStateInterface> PopedState);

	/*状态机中所有状态*/
	TArray<TScriptInterface<IStackStateInterface>> States;


	UPROPERTY(VisibleAnywhere)
	float CurrentStateTime = 0;

	UPROPERTY(BlueprintReadOnly,Category="UIManager")
	int UICount = 1;
	

	


		
};
