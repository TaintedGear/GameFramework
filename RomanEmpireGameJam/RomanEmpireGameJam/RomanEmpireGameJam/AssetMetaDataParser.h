#pragma once
#include "File.h"
#include "Asset.h"
#include "AssetFileTypeExtensions.h"


class AssetMetaDataParser
{
public:
	AssetMetaDataParser();
	~AssetMetaDataParser();

	// Sanity checker to check if the file used is valid for writing or reading to grab metadata from
	bool CheckMetaDataFileIsValid(class File& metaDataFile);

	// Will create meta data for the asset file path entered
	// Extend this to require a file so we can peek and work out default info
	bool CreateMetaData(const std::string& assetFilePath, struct AssetMetaData& metaData);
	
	// Will write the meta data to file in the required formatting
	bool WriteMetaDataToFile(class File& metaDataFile, const struct AssetMetaData& metaData);

	// Will read meta data from a file and return the metadata found
	bool ReadMetaDataFromFile(class File& metaDataFile, struct AssetMetaData& metaData);

private:
	bool WriteCommonMetaData(class File& metaDataFile, const struct AssetMetaData& metaData);
	bool WriteAssetType(class File& metaDataFile, const struct AssetMetaData& metaData);
	bool WriteAssetName(class File& metaDataFile, const struct AssetMetaData& metaData);
	bool WriteAssetPath(class File& metaDataFile, const struct AssetMetaData& metaData);
	bool WriteAssetAttributes(class File& metaDataFile, const struct AssetMetaData& metaData);

	void AddTabLevel();
	void RemoveTabLevel();
	const std::string Tab();
	
	int mTabLevel;

	static const std::string ASSET_TAG,
		ASSET_NAME_TAG,
		ASSET_TYPE_TAG,
		ASSET_PATH_TAG,
		ASSET_ATTRIBUTE_TAG;

	// Holds all the accepted file ext's for assets
	std::unique_ptr<class AssetFileTypeExtensions> mAssetFileTypeExtensions;
};

