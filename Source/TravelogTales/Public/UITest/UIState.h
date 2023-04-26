// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StackStateInterface.h"
#include "Blueprint/UserWidget.h"
#include "UIState.generated.h"

/**
 * 
 */
UCLASS(Abstract,Blueprintable)
class TRAVELOGTALES_API UUIState : public UUserWidget,public IStackStateInterface
{
	GENERATED_BODY()

public:
	/*IStackStateInterface Begin*/
	virtual  void EnterState(EStackAction StackAction) override;
	virtual  void ExitState(EStackAction StackAction) override;
	virtual  void UpdateState(float DeltaTime) override;
	/*IStackStateInterface End*/

	UFUNCTION(BlueprintNativeEvent,Category= "StackState",meta=(DisPlayName = "OnEnterState" ))
	void ReceiveEnterState(EStackAction StackAction);

	UFUNCTION(BlueprintNativeEvent,Category= "StackState",meta=(DisPlayName = "OnExitState" ))
	void ReceiveExitState(EStackAction StackAction);
	
	UFUNCTION(BlueprintNativeEvent,Category= "StackState",meta=(DisPlayName = "OnUpdateState" ))
	void ReceiveUpdateState(float DeltaTime);

	
	
};
