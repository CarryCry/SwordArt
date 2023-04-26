// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIState.h"
#include "UITest/StackStateMachineComponent.h"
#include "UIManagerComponent.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LogUIManager,All,Log);

UENUM(BlueprintType)
enum EUIStateCasResult {Success,Failed };

UCLASS()
class TRAVELOGTALES_API UUIManagerComponent : public UStackStateMachineComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent,Category="UIManager")
	void InitUIStates();

	UFUNCTION(BlueprintPure,BlueprintNativeEvent,Category="UIManager",meta=(DisplayName = "GetUI"))
	UUIState* GetUI(FName UIName);

	UFUNCTION(BlueprintCallable,Category="UIManager",meta=(DisplayName = "PushUIState"))
	void PushUIState(FName UIName);

	/*Help函数 Push+Get*/
	UFUNCTION(BlueprintCallable,Category="UIManager",meta=(ExpandEnumAsExecs="IsValid",DeterminesOutputType = "StateClass",DynamicOutputParam = "OutState"))
	void GetCurrentUIState(TSubclassOf<UUIState>StateClass,TEnumAsByte<EUIStateCasResult>& IsValid,UUIState*& OutState);

	UPROPERTY(EditDefaultsOnly,Category="UIManager")
	TMap<FName,TSubclassOf<UUIState>>UIStates;

	UPROPERTY(BlueprintReadWrite,Category= "UIManager")
	UUIState* UMG_PlayingState;

	UPROPERTY(BlueprintReadWrite,Category= "UIManager")
	FName PlayingStateName = "UMG_PlayingState";
	
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	UPROPERTY()
	TMap<FName,UUIState*> UIInstances;
};
