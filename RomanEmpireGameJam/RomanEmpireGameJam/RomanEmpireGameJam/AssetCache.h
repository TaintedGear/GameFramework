#pragma once

#include "PCH.h"
#include "Log.h"
#include "Asset.h"
#include "AssetLoader.h"
#include "AssetPool.h"
#include "AssetDatabase.h"

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
	AssetCache(
		std::shared_ptr<class AssetLoader<T>> assetLoader,
		std::shared_ptr<class AssetDatabase> assetDatabase);

	virtual ~AssetCache() { };

	// Will return a shared ptr to the asset that is requested, Will reload the asset if it has not been loaded already
	std::shared_ptr<Asset> GetAsset(const std::string& filepath) override;

private:
	bool FindAssetMetaDataFromDatabase(const std::string& filepath, AssetMetaData& metaData);

	// Key: Filepath, Value: Asset<T>
	std::map< std::string, std::weak_ptr<Asset>> mAssetCache;
	
	// Holds the asset loader 
	std::shared_ptr<class AssetLoader<T>> mAssetLoader;

	// AssetPool<T> to hold the memory allocated for the assets
	std::unique_ptr<class AssetPool<T>> mAssetPool;

	std::weak_ptr<class AssetDatabase> mWeakAssetDatabase;
};

//------------------------------------------//
// AssetCache<T>::FindAssetMetaDataFromDatabase				
//------------------------------------------//
template <class T>
bool AssetCache<T>::FindAssetMetaDataFromDatabase(const std::string& filepath, AssetMetaData& metaData)
{
	std::shared_ptr<AssetDatabase> AssetDB = mWeakAssetDatabase.lock();
	if (AssetDB != nullptr)
	{
		AssetMetaData newAssetMetaData;
		if (AssetDB->GetAssetMetaData(filepath, newAssetMetaData))
		{
			//Determine this is of the same type of this asset cache - May not need to do this check
			if (newAssetMetaData.AssetTypeHash == std::type_index(typeid(T)).hash_code())
			{
				metaData = newAssetMetaData;
				return true;
			}
		}
	}

	return false;
}

//------------------------------------------//
// AssetCache<T>::AssetCache				
//------------------------------------------//
template <class T>
AssetCache<T>::AssetCache(
	std::shared_ptr< class AssetLoader<T>> assetLoader,
	std::shared_ptr<class AssetDatabase> assetDatabase)
{
	// Assign the loader that we are using to load these assets
	if (assetLoader == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Asset loader was null when trying to create asset cache");
		mAssetLoader = nullptr;
	}
	else
	{
		mAssetLoader = assetLoader;
	}

	// Store a weak ref of the asset DB
	if (assetDatabase == nullptr)
	{
		Log::GetLog().LogCriticalMsg("AssetDatabase was null when trying to create asset cache");
	}
	else
	{
		mWeakAssetDatabase = assetDatabase;
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

	// Grab the meta data for the asset
	AssetMetaData newMetaData;
	if (!FindAssetMetaDataFromDatabase(filepath, newMetaData))
	{
		Log::GetLog().LogHighMsg("Failed to find metadata for asset at: " + filepath);
		return nullptr;
	}

	//This is creating an empty element or grabbing an existing element and checking if we can share it out
	std::shared_ptr<Asset> assetSharedPtr = mAssetCache[filepath].lock();
	if (assetSharedPtr == nullptr)
	{
		//Request a new object from pool
		assetSharedPtr = mAssetPool->RequestAssetObject(mAssetLoader.get());

		//Assign the metadata to the new asset
		assetSharedPtr->MetaData = newMetaData;

		//Reload the object
		mAssetLoader->LoadAsset(std::static_pointer_cast<T>(assetSharedPtr));

		mAssetCache[filepath] = assetSharedPtr;

		//Return the new reloaded object
		return assetSharedPtr;
	}

	//Returning the existing asset
	return assetSharedPtr;
}
