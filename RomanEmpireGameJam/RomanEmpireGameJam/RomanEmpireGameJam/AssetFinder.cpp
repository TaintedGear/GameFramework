#include "AssetFinder.h"

AssetFinder::AssetFinder(std::weak_ptr< class AssetCache > pAssetCache) :
mAssetCache(pAssetCache)
{
}

AssetFinder::~AssetFinder()
{
}
