#pragma once

#include "AssetFactory.h"
#include "RenderingSystem.h"

// Texture loader requires the rendering system
class TextureAssetFactoryLoader : public AssetFactoryLoader
{
public:
	TextureAssetFactoryLoader(){ };
	TextureAssetFactoryLoader(std::weak_ptr<RenderingSystem> pRenderingSystem);
	
	std::weak_ptr<RenderingSystem> RenderingSystemRef() const { return RenderingSystemWeakRef; }

private:
	std::weak_ptr<RenderingSystem> RenderingSystemWeakRef;
};

// Texture asset factory
class TextureAssetFactory : public AssetFactory
{
public:
	TextureAssetFactory();
	~TextureAssetFactory();

	bool InitializeFactory(AssetFactoryLoader& pAssetFactoryLoader);

	std::shared_ptr<Asset> CreateAsset
		(const std::string& pFilepath,
		const std::string& pFilename) override;

private:
	TextureAssetFactoryLoader mFactoryLoader;
};

