#pragma once

#include "PCH.h"

// ADD THE ASSET FILE PATH + NAME + META DATA INTO THE HANDLE NOT THE ASSET
template<class T>
struct AssetHandle
{
	AssetHandle(std::shared_ptr<T> pAsset)
	{
		Asset = pAsset;
	}

	std::shared_ptr<T> Asset;
};

class Asset
{
public:
	Asset() {};
	Asset(const std::string& pAssetFilepath, const std::string& pAssetFilename);
	virtual ~Asset();

	virtual bool Create();
	virtual void Release();

	//Accessors
	std::string AssetFileName() const { return mAssetFileName; }
	std::string AssetFilePath() const { return mAssetFilePath; }

protected:
	std::string mAssetFileName;
	std::string mAssetFilePath;

};

