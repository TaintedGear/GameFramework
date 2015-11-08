#pragma once

#include "AssetManager.h"

class ApplicationAssetManager : public AssetManager
{
public:
	ApplicationAssetManager();
	virtual ~ApplicationAssetManager();

protected:
	virtual bool RegisterDefaultFactories() override;
};

