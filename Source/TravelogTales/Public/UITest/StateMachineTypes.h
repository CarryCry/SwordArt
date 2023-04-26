// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachineTypes.generated.h"


UENUM()
enum EStackAction {Push,Pop };

DECLARE_LOG_CATEGORY_EXTERN(LogStateMachine,All,Log);
DECLARE_LOG_CATEGORY_EXTERN(LogStackStateMachine,All,Log);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateEnterSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateExitSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateUpDateSignature);

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UStateMachineTypes : public UObject
{
	GENERATED_BODY()
	
};
