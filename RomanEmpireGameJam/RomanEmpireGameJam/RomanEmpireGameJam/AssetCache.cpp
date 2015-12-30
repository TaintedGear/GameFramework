#include "AssetCache.h"
#include "Log.h"

AssetCache::AssetCache()
	:
mRenderingSystem(nullptr)
{
}

AssetCache::~AssetCache()
{
	ShutdownAssetCache();
}

//------------------------------------------//
// AssetManager::DoesFactoryExistForAsset				
//------------------------------------------//
bool AssetCache::DoesLoaderExistForAsset(const std::type_index& pTypeIndex) const
{
	return (mAssetCacheMap.count(pTypeIndex) > 0);
}

//------------------------------------------//
// AssetManager::InitilizeAssetManager				
//------------------------------------------//
bool AssetCache::InitializeAssetCache()
{
	return true;
}

//------------------------------------------//
// AssetManager::ShutdownAssetManager				
//------------------------------------------//
void AssetCache::ShutdownAssetCache()
{
	// Go through all the factories and tell them to shutdown

}