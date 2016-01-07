#pragma once

#include "PCH.h"
#include "Intrinsics.h"
#include "Log.h"
#include "AssetCache.h"
#include "AssetLoader.h"

// Holds all the asset cache's for the different types of asset types
// Will create the loaders and add them to the appropriate cache of the same asset type

class AssetCacheCollection
{
public:
	AssetCacheCollection();
	virtual ~AssetCacheCollection();

	// Can be overridden to include new loaders for asset types
	virtual bool InitilizeAssetCollection();

	template <class T>
	bool CreateAssetCache( std::shared_ptr<AssetLoader<T>> assetLoader);

	template <class T>
	std::shared_ptr<T> GetAsset(const std::string& filepath);
private:

	// Type Hash, AssetCache Interface
	std::map< size_t, std::unique_ptr<class IAssetCache> > mAssetCaches;
};

//------------------------------------------//
// AssetDatabase::CreateAssetCache				
//------------------------------------------//
template <class T>
bool AssetCacheCollection::CreateAssetCache(std::shared_ptr<AssetLoader<T>> assetLoader)
{
	static_assert(std::is_base_of<Asset, T>::value, "Trying to create an AssetCache that is not of base Asset");

	//Check if we already have this in our map
	const std::type_index typeIndex = typeid(T);
	if (mAssetCaches.count(typeIndex.hash_code()) > 0)
	{
		// Log that already have this in the cache
		// Maybe do a check to see its valid
		return false;
	}

	// Check if the asset loader is valid
	if (assetLoader == nullptr)
	{
		Log::GetLog().LogCriticalMsg( BuildStringClass(
			typeIndex,
			"Failed to create AssetCache of type ",
			" as AssetLoader is null"));
		return false;
	}
	
	// Pass the loader into the asset cache to share a shared ptr of that object
	// Create the AssetCache - which will create the asset Pool (Pass through Asset Finder helper?)
	IAssetCache* newAssetCache = nullptr;
	newAssetCache = new AssetCache<T>(assetLoader);

	// Store in the asset cache
	mAssetCaches[typeIndex.hash_code()] = std::unique_ptr<IAssetCache>(newAssetCache);

	return true;
}

//------------------------------------------//
// AssetDatabase::GetAsset				
//------------------------------------------//
template <class T>
std::shared_ptr<T>
AssetCacheCollection::GetAsset(const std::string& filepath)
{
	static_assert(std::is_base_of<Asset, T>::value, "Trying to retrieve asset that is not of base Asset");

	// Grab the type index from this T type
	const std::type_index typeIndex = typeid(T);

	//Check if we have a cache made for this asset
	if (mAssetCaches.count(typeIndex.hash_code()) <= 0)
	{
		Log::GetLog().LogCriticalMsg("Failed to get asset as cache for this type does not exist");
		return nullptr;
	}

	if (mAssetCaches[typeIndex.hash_code()] == nullptr)
	{
		//Log that the cache is null
		return nullptr;
	}

	//Cast to the type wanted by the GetAsset T
	return std::static_pointer_cast<T>(mAssetCaches[typeIndex]->GetAsset(filepath));
}

