#pragma once

#include "AssetFinder.h"

class Entity
{
public:
	Entity( std::shared_ptr<class AssetFinder> pAssetFinder );
	virtual ~Entity();

protected:
	
	//Creation helper proxies
	std::shared_ptr< class AssetFinder > mAssetFinder;

private:
};

