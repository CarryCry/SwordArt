// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TravelogAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UTravelogAssetManager : public UAssetManager
{
	GENERATED_BODY()

	// Singleton-like access to this module's interface. This is just for convenience!
	static UTravelogAssetManager& Get();

	// 1. 异步预加载道具资产
	// 该函数用于预加载资产（例如在游戏启动或关卡加载时）。
	// 加载将在后台异步完成。
	UFUNCTION(BlueprintCallable, Category = "Travelog Asset Manager")
	void PreloadAssets(const TArray<FPrimaryAssetId>& AssetIdsToPreload);

	// 2. 缓存已加载的道具资产
	// 该函数用于缓存已加载的资产以备后用。
	// 这将防止同一资产多次不必要的加载和卸载。
	UFUNCTION(BlueprintCallable, Category = "Travelog Asset Manager")
	void CacheLoadedAsset(FPrimaryAssetId AssetId, UObject* LoadedAsset);

	// 3. 查询特定类型的道具资产
	// 该函数用于查询特定类型的资产（例如武器，盔甲）。
	// 它将返回一个FPrimaryAssetId数组，可以用于加载或卸载资产。
	UFUNCTION(BlueprintCallable, Category = "Travelog Asset Manager")
	TArray<FPrimaryAssetId> QueryAssetsByType(FPrimaryAssetType AssetType);

	// 4. 处理道具创建和销毁
	// 该函数用于创建新的资产实例（例如在装备武器时）。
	// 在不再需要资产实例时（例如卸下武器时），还应处理资产实例的销毁。
	UFUNCTION(BlueprintCallable, Category = "Travelog Asset Manager")
    UObject* CreateAndManageAssetInstance(FPrimaryAssetId AssetId);

	
	UFUNCTION(BlueprintCallable, Category = "Travelog Asset Manager")
	const UObject* GetLoadedAsset(FPrimaryAssetId AssetId) const;

protected:

private:
	TMap<FPrimaryAssetId, UObject*> LoadedAssetCache;
	
};
