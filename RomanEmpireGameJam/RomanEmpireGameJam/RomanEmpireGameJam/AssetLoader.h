#pragma once

#include "PCH.h"
#include "Log.h"
#include "Asset.h"
#include "RenderingSystem.h"
#include "System.h"

//TODO: Add option so that when ref count is <= 1 then we call the unload func unless its set to stay is false
// Resources can be loaded with a stay bool so they are not unloaded when they are <= 1 ref count
// Split the storing of the resources into a new class that holds the object pools? (Is this a big deal?)
// Factory loaders are responsable to hold the weak ref to systems that require to create the AssetHandles +
// loading and unloading the resource

// This classed is to be inherited from, allows injection of systems into the different asset loaders
// To allow for assets to be loaded properly with the correct systems.

class AssetLoaderInjector
{
public:
	AssetLoaderInjector() { };
};

class AssetLoader
{
public:
	AssetLoader(const std::type_index& pAssetType);
	virtual ~AssetLoader();

	// 
	virtual bool InitializeLoader( const AssetLoaderInjector& pAssetLoaderInjector);
	void ShutdownLoader();

	// Get the asset type that this factory is responsible for
	std::type_index GetAssetType() const { return mAssetType; }

	// The child is responsible for loading their version of create asset
	virtual bool LoadAsset(
		const std::string& pFilepath,
		const std::string& pFilename,
		std::shared_ptr<Asset>& pAsset) { return false; };

	//
	virtual void UnloadAsset(Asset* pAsset) {};

public:

	//************************************
	// Method:    GetAsset
	// Returns:   std::shared<I> asset
	// Parameter: const std::string & pFilename
	//************************************
	template< class I >
	std::shared_ptr<I> GetAsset(const std::string& pFilename);
	
protected:
	
	// Add a file extension that is used for this asset type 
	void AddExceptedFileExstention(const std::string& pFileExtension);

private:
	// Check if the file name extension is include in the accepted list
	bool CheckFilenameIsValidWithFileExtensions(const std::string& pFilename);

	// Get the asset file path from filename
	bool GetAssetFilepath(const std::string& pFilename, std::string& pFilepath);

private:
	//Store the asset type that this factory will load
	std::type_index mAssetType;

	//Store all the assets of said asset type <FileName, Asset>
	std::map<std::string, std::shared_ptr<Asset>> mAssetMap;

	//Store all the file extensions that this factory accepts for this asset type
	std::vector<std::string> mAssetAcceptedFileExtension;
};

//--------------------------------------------
//	Template funcs - Defined
//--------------------------------------------

//------------------------------------------//
// AssetFactory::GetAsset				
//------------------------------------------//
template< class I >
std::shared_ptr<I> AssetLoader::GetAsset(const std::string& pFilename)
{
	//Check to make sure the template type is the same as the one we are handling
	std::type_index templatedType = typeid(I);
	if (templatedType != mAssetType)
	{
		std::string failureMsg =
			BuildStringClass(templatedType, " Type", "Does not match type ")
			+ BuildStringClass(mAssetType, "", "When finding Asset!");

		Log::GetLog().LogHighMsg(failureMsg);
		return nullptr;
	}

	//Check if we already have an asset loaded for this filename
	if (mAssetMap.count(pFilename) > 0)
	{
		return std::static_pointer_cast<I>(mAssetMap[pFilename]);
	}

	//Check if the filename is in our accepted file extension list
	if (!CheckFilenameIsValidWithFileExtensions(pFilename))
	{
		return false;
	}

	//Get filepath
	std::string pFilepath = "";
	if (!GetAssetFilepath(pFilename, pFilepath))
	{
		return false;
	}

	//If we dont go find it and create it
	std::shared_ptr<Asset> newAsset = nullptr;
	newAsset = CreateAsset(pFilepath, pFilepath);

	if (newAsset == nullptr)
	{
		Log::GetLog().LogHighMsg("Failed to create Asset");
		return nullptr;
	}

	//Add to the asset map
	if (!mAssetMap.emplace(pFilename, newAsset).second)
	{
		Log::GetLog().LogHighMsg("Failed to store Asset into asset map!");
		return nullptr;
	}

	Log::GetLog().LogLowMsg("Created Asset: " + pFilename);
	return std::static_pointer_cast<I>(mAssetMap[pFilename]);
}