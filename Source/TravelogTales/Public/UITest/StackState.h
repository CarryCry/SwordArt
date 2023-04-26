// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StackStateInterface.h"
#include "UObject/NoExportTypes.h"
#include "StackState.generated.h"

/**
 * 
 */
UCLASS(Abstract,BlueprintType,HideCategories=("Cooking","LOD","Physics","Activation","Tags","Rendering"))
class TRAVELOGTALES_API UStackState : public UObject,public IStackStateInterface
{
	GENERATED_BODY()

public:
	/*IStackStateInterface Begin*/
	virtual  void EnterState(EStackAction StackAction) override;
	virtual  void ExitState(EStackAction StackAction) override;
	virtual  void UpdateState(float DeltaTime) override;
	/*IStackStateInterface End*/

	UFUNCTION(BlueprintImplementableEvent,Category= "StackState",meta=(DisPlayName = "OnEnterState" ))
	void ReceiveEnterState(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent,Category= "StackState",meta=(DisPlayName = "OnExitState" ))
    void ReceiveExitState(EStackAction StackAction);
	
	UFUNCTION(BlueprintImplementableEvent,Category= "StackState",meta=(DisPlayName = "OnUpdateState" ))
    void ReceiveUpdateState(float DeltaTime);
	
};
