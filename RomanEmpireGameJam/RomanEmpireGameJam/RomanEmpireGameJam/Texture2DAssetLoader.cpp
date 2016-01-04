#include "Texture2DAssetLoader.h"
#include "PCH.h"
#include "Log.h"

Texture2DAssetLoader::Texture2DAssetLoader() : AssetLoader<Texture2D>()
{
}


Texture2DAssetLoader::~Texture2DAssetLoader()
{
}

//------------------------------------------//
// Texture2DAssetLoader::LoadAsset				
//------------------------------------------//
bool Texture2DAssetLoader::LoadAsset( std::shared_ptr<Texture2D> unloadedAsset)
{
	//Grab the metadata from the asset
	unloadedAsset->MetaData().AssetFilePath;

	return false;
}

//------------------------------------------//
// Texture2DAssetLoader::UnloadAsset				
//------------------------------------------//
void Texture2DAssetLoader::UnloadAsset(Texture2D* asset)
{
	Log::GetLog().LogCriticalMsg("WE are in the texture2D asset Loader unload function");
}
