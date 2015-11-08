#pragma once

#include "PCH.h"

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

