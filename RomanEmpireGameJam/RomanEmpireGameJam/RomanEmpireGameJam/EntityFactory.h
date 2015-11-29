#pragma once

#include "PCH.h"
#include "AssetCache.h"
#include "AssetFinder.h"

//Creates the entitys

class EntityFactory
{
public:
	EntityFactory(std::shared_ptr<class AssetCache> pAssetCache);
	~EntityFactory();

	template<typename T>
	std::shared_ptr<EntityFactory> CreateEntity()
	{
		// Create the entity

	}

private:
	// To be passed down to all the entitys that are created
	class std::shared_ptr<AssetFinder> mAssetFinder;
};

