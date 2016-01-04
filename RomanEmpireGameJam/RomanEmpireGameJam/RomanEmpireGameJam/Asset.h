#pragma once

#include "PCH.h"
#include "AssetMetaData.h"

class Asset
{
public:
	Asset();
	virtual ~Asset();

	const struct AssetMetaData MetaData() { return mAssetData; };
	
protected:
	struct AssetMetaData mAssetData;
};

