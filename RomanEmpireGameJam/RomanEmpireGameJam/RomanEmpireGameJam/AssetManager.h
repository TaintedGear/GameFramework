#pragma once

#include "PCH.h"
#include "Log.h"
#include "AssetFactory.h"
#include "Asset.h"
#include "Intrinsics.h"
#include "RenderingSystem.h"

//Collection of factories that allow them to map their corresponding type

class AssetManager
{
public:
	AssetManager();
	virtual ~AssetManager();

	//Maybe move this dependency of the renderer to child so that if they need it then can get it themselves (Maybe?)
	virtual bool InitializeAssetManager(std::shared_ptr<class RenderingSystem> pRenderer);
	virtual void ShutdownAssetManager();
	
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
	bool RegisterFactory();
	
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

protected:
	// Allow the children to register a bunch of default factories on init
		virtual bool RegisterDefaultFactories();

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
bool AssetManager::DoesFactoryExistForAsset() const
{
	return (mAssetFactoryMap.count(typeid(C)) > 0);
}

//------------------------------------------//
// AssetManager::RegisterFactory				
//------------------------------------------//
template< class F >
bool AssetManager::RegisterFactory()
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

	if (!newFactory->InitializeFactory(mRenderingSystem))
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
AssetManager::GetAsset(const std::string& pFileName, bool& pReturn)
{
	AssetHandle<P> foundAssetHandle{ nullptr };

	//Find asset
	std::shared_ptr<Asset> foundAsset = nullptr;
	if (FindAssetInFactory<P>(pFileName))
	{
		pReturn = false;
	}

	return foundAssetHandle;
}

//------------------------------------------//
// AssetManager::FindAssetInFactory				
//------------------------------------------//
template< class I >
std::shared_ptr<I>
AssetManager::FindAssetInFactory(const std::string& pFilename)
{
	std::type_index assetType = typeid(I);
	if (!DoesFactoryExistForAsset(assetType))
	{
		return nullptr;
	}

	//Grab the factory from the map 
	std::shared_ptr<AssetFactory> factoryForThisAsset = mAssetFactoryMap[assetType];
	if (factoryForThisAsset == nullptr)
	{
		return nullptr;
	}

	std::shared_ptr<I> foundAsset = nullptr;
	//Call get asset funct
	foundAsset = factoryForThisAsset->GetAsset<I>(pFilename);
	//If this returned null then we still get the same result to the caller
	return foundAsset;
}
