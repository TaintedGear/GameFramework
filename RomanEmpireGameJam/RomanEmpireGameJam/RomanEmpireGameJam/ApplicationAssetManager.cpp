#include "ApplicationAssetManager.h"

#include "TextureAssetFactory.h"
#include "Texture.h"

ApplicationAssetManager::ApplicationAssetManager()
{

}

ApplicationAssetManager::~ApplicationAssetManager()
{
}

//------------------------------------------//
// ApplicationAssetManager::LoadDefaultFactories				
//------------------------------------------//
bool ApplicationAssetManager::RegisterDefaultFactories()
{
	if (!DoesFactoryExistForAsset<Texture>())
	{
		if ( !RegisterFactory<TextureAssetFactory>() )
		{
			return false;
		}
	}

	return true;
}
