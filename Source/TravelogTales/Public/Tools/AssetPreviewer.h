// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "AssetPreviewer.generated.h"

/**
 * 
 */

UCLASS()
class TRAVELOGTALES_API UAssetPreviewer : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
	UObject* SelectedAsset;

	UFUNCTION(BlueprintCallable, Category = "Preview")
	void OnAssetSelected(UObject* NewSelectedAsset)
	{
		SelectedAsset = NewSelectedAsset;
		// 在蓝图中设置预览组件的StaticMesh或SkeletalMesh属性
	}
	
};
