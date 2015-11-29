#pragma once

#include "AssetCache.h"
#include "RenderingSystem.h"

class ApplicationAssetCache : public AssetCache
{
public:
	ApplicationAssetCache();
	virtual ~ApplicationAssetCache();
	
	//Passes through the systems that are required to set up default asset factories for the asset cache
	bool InitializeAssetCache(
		std::shared_ptr<class RenderingSystem> pRenderingSystem);
};

