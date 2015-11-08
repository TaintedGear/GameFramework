#pragma once

#include "AssetFactory.h"

class TextureAssetFactory : public AssetFactory
{
public:
	TextureAssetFactory();
	virtual ~TextureAssetFactory();

	virtual std::shared_ptr<Asset> CreateAsset
		(const std::string& pFilepath,
		const std::string& pFilename) override;
};

