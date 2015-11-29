#include "EntityFactory.h"

EntityFactory::EntityFactory(std::shared_ptr<class AssetCache> pAssetCache)
{
	if (pAssetCache == nullptr)
	{
		Log::GetLog().LogCriticalMsg("Asset manager was invalid when creating the EntityFactory");
	}
	else
	{
		std::weak_ptr<AssetCache> assetManagerWeak;
		assetManagerWeak = pAssetCache;

		mAssetFinder = std::make_shared<AssetFinder>(assetManagerWeak);
	}
}

EntityFactory::~EntityFactory()
{
}
