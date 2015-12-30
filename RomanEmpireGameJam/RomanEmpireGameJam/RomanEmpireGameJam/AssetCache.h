#pragma once

#include "PCH.h"
#include "Log.h"
#include "AssetLoader.h"
#include "AssetPool.h"
#include "Asset.h"
#include "Intrinsics.h"
#include "RenderingSystem.h"

// Collection of loaders that allow them to map their corresponding type
class AssetCache
{
public:
	AssetCache();
	virtual ~AssetCache();

	//Maybe move this dependency of the renderer to child so that if they need it then can get it themselves (Maybe?)
	virtual bool InitializeAssetCache();
	virtual void ShutdownAssetCache();
	
	bool DoesLoaderExistForAsset(const std::type_index& pTypeIndex) const;

//--------------------------------------------
//	Template funcs - Definition
//--------------------------------------------
public:

	//************************************
	// Method:    RegisterLoader
	// Returns:   bool
	//************************************
	template< typename AssetType, typename AssetLoaderType >
	bool RegisterLoader( const AssetLoaderInjector& pAssetLoaderInjector );
	
	//************************************
	// Method:    DoesFactoryExistForAsset
	// Returns:   bool
	//************************************
	template< class AssetType >
	bool DoesLoaderExistForAsset() const;

	//------------------------------------------//
	// AssetManager::GetAsset				
	//------------------------------------------//
	template< class AssetType >
	bool GetAsset(const std::string& pFileName, AssetHandle<AssetType>& pAssetHandle );

	//------------------------------------------//
	// FindAssetInFactory				
	//------------------------------------------//
	template< class AssetType >
	std::shared_ptr<AssetType> FindAsset(const std::string& pFilename);

private:

	// Helper to store both loader and asset pool together
	struct AssetWrapper
	{
		std::shared_ptr< class IAssetPool> mAssetPool;
		std::shared_ptr< class AssetLoader> mAssetLoader;
	};

	// Asset loader map with a key of the asset type to determine what loader to use
	std::map< std::type_index, AssetWrapper > mAssetCacheMap;

	// Ref to the rendering system to pass down to factories
	std::shared_ptr<class RenderingSystem> mRenderingSystem;

};

//------------------------------------------//
// AssetManager::DoesFactoryExistForAsset				
//------------------------------------------//
template< class AssetType >
bool AssetCache::DoesLoaderExistForAsset() const
{
	return (mAssetCacheMap.count(typeid(AssetType)) > 0);
}

//------------------------------------------//
// AssetManager::RegisterFactory				
//------------------------------------------//
template< class AssetType, class AssetLoaderType >
bool AssetCache::RegisterLoader( const AssetLoaderInjector& pAssetLoaderInjector )
{
	// Create the new registered loader
	std::shared_ptr<AssetLoader> newLoader = nullptr;
	newLoader = std::make_shared<AssetLoaderType>();

	if (newLoader == nullptr)
	{
		std::string failureMsg = BuildStringClass(typeid(AssetLoaderType), "Failed to create and register ", " In asset manager!");
		Log::GetLog().LogHighMsg(failureMsg);
		return false;
	}

	// Check if this loader matches this asset
	const std::type_index assetType = typeid(AssetType);
	if (newLoader->GetAssetType() != assetType)
	{
		return false;
	}

	if (!newLoader->InitializeLoader(pAssetLoaderInjector))
	{
		std::string failureMsg = BuildStringClass(typeid(newLoader), "Failed to Initialize ", " In asset manager!");
		Log::GetLog().LogHighMsg(failureMsg);
		return false;
	}

	// Create the associated Asset Pool - TODO add budget into this when needed
	std::shared_ptr<IAssetPool> newPool = nullptr;
	newPool = std::make_shared<AssetPool<AssetType>>(50);

	// Wrap the asset loader and pool together
	AssetWrapper newAssetWrapper;
	newPool.swap(newAssetWrapper.mAssetPool);
	newLoader.swap(newAssetWrapper.mAssetLoader);

	// Store the AssetWrapper in the cache
	if (!mAssetCacheMap.emplace(assetType, newAssetWrapper).second)
	{
		std::string warningMsg = BuildStringClass(assetType, "Loader ", " is already registered!");
		Log::GetLog().LogHighMsg(warningMsg);
	}

	// Make sure we successfully stored the object into the factory map
	if (mAssetCacheMap[assetType].mAssetLoader == nullptr || mAssetCacheMap[assetType].mAssetPool == nullptr)
	{
		std::string failureMsg = BuildStringClass(assetType, "Failed to store ", " In to Loader map for asset manager!");
		Log::GetLog().LogHighMsg(failureMsg);

		return false;
	}

	return true;
}

//------------------------------------------//
// AssetManager::GetAsset				
//------------------------------------------//
template< class AssetType >
bool AssetCache::GetAsset(const std::string& pFileName, AssetHandle<AssetType>& pAssetHandle)
{
	AssetHandle<AssetType> foundAssetHandle{ nullptr };
	pAssetHandle = foundAssetHandle;

	std::type_index assetType = typeid(AssetType);
	if (!DoesLoaderExistForAsset(assetType))
	{
		Log::GetLog().LogHighMsg("Asset Loader for " + BuildStringClass(assetType) + " is not registered for this asset manager");
		return false;
	}

	// Find asset if it exists already
	std::shared_ptr<Asset> asset = nullptr;
	asset = FindAsset<AssetType>(pFileName);

	// Asset already exists return that with the wrapped handle
	if ( asset != nullptr )
	{
		foundAssetHandle.Asset = std::static_pointer_cast<AssetType>(asset);
		return true;
	}

	// Check the asset loader and pool from the wrapper
	if (mAssetCacheMap[assetType].mAssetLoader == nullptr)
	{
		Log::GetLog().LogHighMsg("Asset loader when finding asset was nullptr");
		return false;
	}
	if (mAssetCacheMap[assetType].mAssetPool == nullptr)
	{
		Log::GetLog().LogHighMsg("Asset pool when finding asset was nullptr");
		return false;
	}

	//Request for an object
	if (!mAssetCacheMap[assetType].mAssetPool->RequestAssetObject(
		mAssetCacheMap[assetType].mAssetLoader.get(),
		asset))
	{
		return false;
	}

	if (!mAssetCacheMap[assetType].mAssetLoader->LoadAsset(pFileName, "", asset))
	{
		//Failed to load
		return false;
	}

	foundAssetHandle.Asset = std::static_pointer_cast<AssetType>(asset);

	Log::GetLog().LogLowMsg("Got asset " + pFileName);

	return true;
}

//------------------------------------------//
// AssetManager::FindAssetInFactory				
//------------------------------------------//
template< class AssetType >
std::shared_ptr<AssetType> AssetCache::FindAsset(const std::string& pFilename)
{
	std::type_index assetType = typeid(AssetType);
	if (!DoesLoaderExistForAsset(assetType))
	{
		Log::GetLog().LogHighMsg("Asset Factory for " + BuildStringClass(assetType) + " is not registered for this asset manager");
		return nullptr;
	}

	// Get the Asset Wrapper from the AssetCache
	if (mAssetCacheMap[assetType].mAssetLoader == nullptr)
	{
		Log::GetLog().LogHighMsg("Asset loader when finding asset was nullptr");
		return nullptr;
	}
	if (mAssetCacheMap[assetType].mAssetPool == nullptr)
	{
		Log::GetLog().LogHighMsg("Asset pool when finding asset was nullptr");
		return nullptr;
	}

	// Go through the allocated objects in the pool and find if it already exists
	std::shared_ptr<Asset> foundAsset = nullptr;
	if(!mAssetCacheMap[assetType].mAssetPool->FindAssetObject(pFilename, foundAsset))
	{
		Log::GetLog().LogHighMsg("Could not find asset in asset pool");
		return nullptr;
	}

	return std::static_pointer_cast<AssetType>(foundAsset);
}

