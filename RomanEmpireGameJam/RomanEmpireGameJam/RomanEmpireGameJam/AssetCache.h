#pragma once

#include "PCH.h"
#include "Log.h"
#include "Asset.h"
#include "AssetLoader.h"
#include "AssetPool.h"

// Interface for AssetCache<T>
class IAssetCache
{
public:
	IAssetCache(){};
	~IAssetCache(){};

	virtual std::shared_ptr<Asset> GetAsset(const std::string& filepath) = 0;
};

template <class T> class AssetCache : public IAssetCache
{
public:	
	// Static assert if this is not of type Asset
	static_assert(std::is_base_of<class Asset, T>::value, "AssetCache<T> is not of base Asset.");

	// Pass through the loader for the asset type
	AssetCache(std::shared_ptr<class AssetLoader<T>> assetLoader);
	virtual ~AssetCache() { };

	// Will return a shared ptr to the asset that is requested, Will reload the asset if it has not been loaded already
	std::shared_ptr<Asset> GetAsset(const std::string& filepath) override;

private:
	// Holds the assets with the filepath as the key
	std::map< std::string, std::weak_ptr<T>> mAssetCache;
	
	// Holds the asset loader 
	std::shared_ptr<class AssetLoader<T>> mAssetLoader;

	// AssetPool<T> to hold the memory allocated for the assets
	std::unique_ptr<class AssetPool<T>> mAssetPool;
};

//------------------------------------------//
// AssetCache<T>::AssetCache				
//------------------------------------------//
template <class T>
AssetCache<T>::AssetCache(std::shared_ptr< class AssetLoader<T>> assetLoader)
{
	// Assign the loader that we are using to load these assets
	if (assetLoader == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Asset loader was null when trying to create asset cache");
	}
	else
	{
		mAssetLoader = assetLoader;
	}

	// Create an asset pool to store the memory
	AssetPool<T>* assetPool = new AssetPool<T>();
	mAssetPool = std::unique_ptr<AssetPool<T>>(assetPool);
}

//------------------------------------------//
// AssetCache<T>::GetAsset				
//------------------------------------------//
template <class T>
std::shared_ptr<Asset> AssetCache<T>::GetAsset(const std::string& filepath)
{
	// Sanity check the filepath
	if (filepath.length() <= 0)
	{
		//Log
		return nullptr;
	}

	// Check if we have a value at this key in the cache
	if (mAssetCache.count(filepath) <= 0)
	{
		// We dont currently have this asset added
		// Go find the asset data from DB
		return nullptr;
	}

	std::shared_ptr<Asset> assetSharedPtr = mAssetCache[filepath].lock();
	if (assetSharedPtr == nullptr)
	{
		//Request a new object from pool
		assetSharedPtr = mAssetPool->RequestAssetObject(mAssetLoader.get());

		//Reload the object
		mAssetLoader->LoadAsset(std::static_pointer_cast<T>(assetSharedPtr));

		//Return the new reloaded object
		return assetSharedPtr;
	}

	return assetSharedPtr;
}
