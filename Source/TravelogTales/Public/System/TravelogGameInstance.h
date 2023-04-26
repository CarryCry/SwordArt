// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/UIManager.h"
#include "TravelogGameInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TRAVELOGTALES_API UTravelogGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	

private:
	// UI管理器
	UPROPERTY()
	UUIManager* UIManager;
};
