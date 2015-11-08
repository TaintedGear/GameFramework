#include "AssetManager.h"
#include "Log.h"
#include "FileHelper.h"
#include "FilePaths.h"

AssetManager::AssetManager() 
	:
mRenderingSystem(nullptr)
{
}

AssetManager::~AssetManager()
{
	ShutdownAssetManager();
}

//------------------------------------------//
// AssetManager::DoesFactoryExistForAsset				
//------------------------------------------//
bool AssetManager::DoesFactoryExistForAsset(const std::type_index& pTypeIndex) const
{
	return ( mAssetFactoryMap.count(pTypeIndex) > 0 );
}

//------------------------------------------//
// AssetManager::LoadDefaultFactories				
//------------------------------------------//
bool AssetManager::RegisterDefaultFactories()
{
	Log::GetLog().LogLowMsg("No Default factories set when registering from asset manager!");
	return true;
}

//------------------------------------------//
// AssetManager::InitilizeAssetManager				
//------------------------------------------//
bool AssetManager::InitializeAssetManager(std::shared_ptr<RenderingSystem> pRenderer)
{
	mRenderingSystem = pRenderer;

	if (mRenderingSystem == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Rendering system is null when initializing asset manager!");
		return false;
	}

	if (!RegisterDefaultFactories())
	{
		Log::GetLog().LogCriticalMsg("Failed to load the default factories for asset manager!");
		return false;
	}

	return true;
}

//------------------------------------------//
// AssetManager::ShutdownAssetManager				
//------------------------------------------//
void AssetManager::ShutdownAssetManager()
{
	// Go through all the managers and tell them to shutdown

}

