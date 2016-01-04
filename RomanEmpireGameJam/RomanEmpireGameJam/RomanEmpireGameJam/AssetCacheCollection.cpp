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
bool AssetCacheCollection::InitilizeAssetCollection()
{
	std::shared_ptr<Texture2DAssetLoader> texture2DAssetLoader = nullptr;
	texture2DAssetLoader = std::make_shared<Texture2DAssetLoader>();

	if (!CreateAssetCache<Texture2D>(texture2DAssetLoader))
	{
		return false;
	}

	return true;
}
