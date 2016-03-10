#pragma once

#include "PCH.h"
#include "AssetMetaData.h"

class Asset
{
public:
	Asset();
	virtual ~Asset();

	struct AssetMetaData MetaData;
};

