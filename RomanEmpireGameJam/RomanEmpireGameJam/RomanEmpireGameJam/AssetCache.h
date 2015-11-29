#pragma once

#include "PCH.h"
#include "Log.h"
#include "AssetFactory.h"
#include "Asset.h"
#include "Intrinsics.h"
#include "RenderingSystem.h"

//Collection of factories that allow them to map their corresponding type

class AssetCache
{
public:
	AssetCache();
	virtual ~AssetCache();

	//Maybe move this dependency of the renderer to child so that if they need it then can get it themselves (Maybe?)
	virtual bool InitializeAssetCache();
	virtual void ShutdownAssetCache();
	
	bool DoesFactoryExistForAsset(const std::type_index& pTypeIndex) const;

//--------------------------------------------
//	Template funcs - Definition
//--------------------------------------------
public:

	//************************************
	// Method:    RegisterFactory
	// Returns:   bool
	//************************************
	template< class F >
	bool RegisterFactory(AssetFactoryLoader& pAssetFactoryLoader);
	
	//************************************
	// Method:    DoesFactoryExistForAsset
	// Returns:   bool
	//************************************
	template< class C >
	bool DoesFactoryExistForAsset() const;

	//------------------------------------------//
	// AssetManager::GetAsset				
	//------------------------------------------//
	template< class P >
	AssetHandle<P> GetAsset(const std::string& pFileName, bool& pReturn);

	//------------------------------------------//
	// FindAssetInFactory				
	//------------------------------------------//
	template< class I >
	std::shared_ptr<I> FindAssetInFactory( const std::string& pFilename);

private:
	// Asset Factory map with a key of the asset type index to determine what factory to use
	std::map< std::type_index, std::shared_ptr<class AssetFactory> > mAssetFactoryMap;

	// Ref to the rendering system to pass down to factories
	std::shared_ptr<class RenderingSystem> mRenderingSystem;
};

//------------------------------------------//
// AssetManager::DoesFactoryExistForAsset				
//------------------------------------------//
template< class C >
bool AssetCache::DoesFactoryExistForAsset() const
{
	return (mAssetFactoryMap.count(typeid(C)) > 0);
}

//------------------------------------------//
// AssetManager::RegisterFactory				
//------------------------------------------//
template< class F >
bool AssetCache::RegisterFactory(AssetFactoryLoader& pAssetFactoryLoader)
{
	// Create the new registered factory
	std::shared_ptr<AssetFactory> newFactory = nullptr;
	newFactory = std::make_shared<F>();

	if (newFactory == nullptr)
	{
		std::string failureMsg = BuildStringClass(typeid(F), "Failed to create and register ", " In asset manager!");
		Log::GetLog().LogHighMsg(failureMsg);
		return false;
	}

	if (!newFactory->InitializeFactory(pAssetFactoryLoader))
	{
		std::string failureMsg = BuildStringClass(typeid(F), "Failed to Initialize ", " In asset manager!");
		Log::GetLog().LogHighMsg(failureMsg);
		return false;
	}

	//Grab the asset type
	std::type_index factoryAssetType = newFactory->GetAssetType();

	// Store in the map with the relevant asset type - if false then we already have it
	if (!mAssetFactoryMap.emplace(factoryAssetType, newFactory).second)
	{
		std::string warningMsg = BuildStringClass(typeid(F), "Factory ", " is already registered!");
		Log::GetLog().LogHighMsg(warningMsg);
	}

	// Make sure we successfully stored the object into the factory map
	if (mAssetFactoryMap[factoryAssetType] == nullptr)
	{
		std::string failureMsg = BuildStringClass(typeid(F), "Failed to store ", " In to factory map for asset manager!");
		Log::GetLog().LogHighMsg(failureMsg);

		return false;
	}

	return true;
}

//------------------------------------------//
// AssetManager::GetAsset				
//------------------------------------------//
template< class P >
AssetHandle<P>
AssetCache::GetAsset(const std::string& pFileName, bool& pReturn)
{
	AssetHandle<P> foundAssetHandle{ nullptr };

	//Find asset
	std::shared_ptr<Asset> foundAsset = nullptr;
	if (!FindAssetInFactory<P>(pFileName))
	{
		Log::GetLog().LogHighMsg(
			"Failed to get asset " +
			pFileName +
			" of " +
			BuildStringClass(typeid(P)));

		pReturn = false;
		return nullptr;
	}

	Log::GetLog().LogLowMsg("Got asset " + pFileName);
	
	pReturn = true;
	return foundAssetHandle;
}

//------------------------------------------//
// AssetManager::FindAssetInFactory				
//------------------------------------------//
template< class I >
std::shared_ptr<I>
AssetCache::FindAssetInFactory(const std::string& pFilename)
{
	std::type_index assetType = typeid(I);
	if (!DoesFactoryExistForAsset(assetType))
	{
		Log::GetLog().LogHighMsg("Asset Factory for " + BuildStringClass(assetType) + " is not registered for this asset manager");
		return nullptr;
	}

	//Grab the factory from the map 
	std::shared_ptr<AssetFactory> factoryForThisAsset = mAssetFactoryMap[assetType];
	if (factoryForThisAsset == nullptr)
	{
		Log::GetLog().LogHighMsg("Asset Factory for " + BuildStringClass(assetType) + " is null for this asset manager");
		return nullptr;
	}

	// Call the factorys get asset function
	std::shared_ptr<I> foundAsset = nullptr;
	foundAsset = factoryForThisAsset->GetAsset<I>(pFilename);

	//If this returned null then we still get the same result to the caller
	return foundAsset;
}