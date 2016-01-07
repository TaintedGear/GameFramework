#pragma once

#include "PCH.h"
#include "Asset.h"
#include "AssetMetaData.h"
#include "AssetMetaDataParser.h"

// Will discover assets on load to store and create meta data for asset files
// Will hold all the AssetCache's - loaders and pools
// Will also create proxies to allow entities to ask for assets
// Main interface to loading assets

class AssetDatabase
{
public:
	AssetDatabase();
	~AssetDatabase();

	void DiscoverAssets(); 

private:
	bool CreateMetaDataFile(const std::string& assetFilePath);
	bool ReadMetaDataFile(const std::string& metaDataFilePath);

	// Holds all the metadata of the assets in the project
	std::map< std::string, AssetMetaData > mAssetMetaData;

	class AssetMetaDataParser mAssetMetaDataParser;
};

