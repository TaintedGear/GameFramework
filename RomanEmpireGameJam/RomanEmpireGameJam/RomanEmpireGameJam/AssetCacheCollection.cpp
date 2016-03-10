#include "AssetCacheCollection.h"

//TEST
#include "Texture2DAssetLoader.h"

AssetCacheCollection::AssetCacheCollection()
{
}


AssetCacheCollection::~AssetCacheCollection()
{
}

//------------------------------------------//
// AssetDatabase::InitilizeAssetDatabase				
//------------------------------------------//
bool AssetCacheCollection::InitilizeAssetCollection(
	std::weak_ptr<class Renderer> pRenderer,
	std::shared_ptr<class AssetDatabase> assetDatabase)
{
	//check if the asset database is valid
	if (assetDatabase == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Asset database was null when init of the asset cache collection ran");
		return false;
	}

	mAssetDatabase = assetDatabase;

	std::shared_ptr<Texture2DAssetLoader> texture2DAssetLoader = nullptr;
	texture2DAssetLoader = std::make_shared<Texture2DAssetLoader>();

	if (!texture2DAssetLoader->StartupLoader(pRenderer))
	{
		return false;
	}

	if (!CreateAssetCache<Texture2D>(texture2DAssetLoader))
	{
		return false;
	}

	return true;
}
