#pragma once

#include "AssetLoader.h"
#include "RenderingSystem.h"

// Texture loader requires the rendering system
class TextureAssetLoaderInjector : public AssetLoaderInjector
{
public:
	TextureAssetLoaderInjector(){ };
	TextureAssetLoaderInjector(std::weak_ptr<RenderingSystem> pRenderingSystem);
	
	std::weak_ptr<RenderingSystem> RenderingSystemRef() const { return RenderingSystemWeakRef; }

private:
	std::weak_ptr<RenderingSystem> RenderingSystemWeakRef;
};

// Texture asset factory
class TextureAssetLoader : public AssetLoader
{
public:
	TextureAssetLoader();
	~TextureAssetLoader();

	bool InitializeLoader(AssetLoaderInjector& pAssetFactoryLoader) override;

	std::shared_ptr<Asset> CreateAsset
		(const std::string& pFilepath,
		const std::string& pFilename) override;

private:
	TextureAssetLoaderInjector mInjector;
};

