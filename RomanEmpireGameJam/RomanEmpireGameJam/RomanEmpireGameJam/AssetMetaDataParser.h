#pragma once
#include "File.h"
#include "Asset.h"

class AssetMetaDataParser
{
public:
	AssetMetaDataParser();
	~AssetMetaDataParser();

	bool CheckMetaDataFileIsValid(class File& metaDataFile);
	bool WriteMetaData(class File& metaDataFile, const struct AssetMetaData& metaData);
	bool ReadMetaData(class File& metaDataFile, struct AssetMetaData& metaData);

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
};

