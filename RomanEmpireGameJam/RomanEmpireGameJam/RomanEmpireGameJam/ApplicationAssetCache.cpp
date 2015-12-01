#include "ApplicationAssetCache.h"

#include "TextureAssetLoader.h"
#include "Texture.h"

#include "Log.h"

ApplicationAssetCache::ApplicationAssetCache()
{

}

ApplicationAssetCache::~ApplicationAssetCache()
{
}

//------------------------------------------//
// ApplicationAssetManager::InitializeAssetManager				
//------------------------------------------//
bool ApplicationAssetCache::InitializeAssetCache(std::shared_ptr<class RenderingSystem> pRenderingSystem)
{
	if (pRenderingSystem == nullptr)
	{
		//LOG
		return false;
	}

	if (!DoesLoaderExistForAsset<Texture>())
	{
		//Create the texture asset factor loader and register it
		std::weak_ptr<RenderingSystem> renderingSystemWeak = pRenderingSystem;
		TextureAssetLoaderInjector textureAssetLoaderInjector(renderingSystemWeak);

		if (!RegisterLoader<TextureAssetLoader>(textureAssetLoaderInjector))
		{
			Log::GetLog().LogCriticalMsg("Failed to register Texture asset factory");
			return false;
		}
	}

	return true;
}
