#pragma once

#include "PCH.h"
#include "AssetCache.h"
#include "Asset.h"

// Proxy class for the asset manager
class AssetFinder
{
public:
	//Inject the asset manager into this so we have access to get the assets
	AssetFinder(std::weak_ptr<class AssetCache> pAssetCache);
	~AssetFinder();

	template<typename T>
	AssetHandle<T> GetAsset(std::string pFilepath)
	{
		AssetHandle<T> newAssetHandle;

		std::shared_ptr<AssetCache> assetCacheShared = mAssetCache.lock();
		if (assetCacheShared != nullptr)
		{
			newAssetHandle = assetCacheShared->GetAsset<T>(pFilepath);
		}
		else
		{
			Log::GetLog().LogHighMsg("AssetCache has gone out of scope, when getting asset from asset finder");
		}

		return newAssetHandle;
	}

private:
	std::weak_ptr<AssetCache> mAssetCache;
};

