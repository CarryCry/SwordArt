// Fill out your copyright notice in the Description page of Project Settings.


#include "System/TravelogAssetManager.h"

UTravelogAssetManager& UTravelogAssetManager::Get()
{
	UTravelogAssetManager* Instance = Cast<UTravelogAssetManager>(GEngine->AssetManager);
	check(Instance);
	return *Instance;
}

void UTravelogAssetManager::PreloadAssets(const TArray<FPrimaryAssetId>& AssetIdsToPreload)
{
	// 异步预加载道具资产
	TArray<FSoftObjectPath> AssetReferencesToPreload;
	for (const FPrimaryAssetId& AssetId : AssetIdsToPreload)
	{
		AssetReferencesToPreload.Add(GetPrimaryAssetPath(AssetId));
	}
	StreamableManager.RequestAsyncLoad(AssetReferencesToPreload, FStreamableDelegate());
}

void UTravelogAssetManager::CacheLoadedAsset(FPrimaryAssetId AssetId, UObject* LoadedAsset)
{
	// 缓存已加载的道具资产
	if (!LoadedAsset)
	{
		return;
	}
	LoadedAssetCache.Add(AssetId, LoadedAsset);
}

TArray<FPrimaryAssetId> UTravelogAssetManager::QueryAssetsByType(FPrimaryAssetType AssetType)
{
	// 查询特定类型的道具资产
	TArray<FPrimaryAssetId> FoundAssetIds;
	GetPrimaryAssetIdList(AssetType, FoundAssetIds);
	return FoundAssetIds;
}

UObject* UTravelogAssetManager::CreateAndManageAssetInstance(FPrimaryAssetId AssetId)
{
	// 处理道具创建和销毁
	UObject* AssetInstance = GetPrimaryAssetObject(AssetId);
	if (AssetInstance)
	{
		// 如果资产已加载，则创建一个新实例
		AssetInstance = DuplicateObject(AssetInstance, nullptr);
	}
	else
	{
		// 如果资产未加载，则尝试同步加载，并创建一个新实例
		UObject* LoadedAsset = GetPrimaryAssetObject(AssetId);
		if (LoadedAsset)
		{
			AssetInstance = DuplicateObject(LoadedAsset, nullptr);
		}
	}
	return AssetInstance;
}

const UObject* UTravelogAssetManager::GetLoadedAsset(FPrimaryAssetId AssetId) const
{
	const UObject* const* FoundAsset = LoadedAssetCache.Find(AssetId);
	return FoundAsset ? *FoundAsset : nullptr;
}



