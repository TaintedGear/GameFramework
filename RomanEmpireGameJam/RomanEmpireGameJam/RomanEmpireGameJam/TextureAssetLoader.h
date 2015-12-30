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

	bool InitializeLoader(const AssetLoaderInjector& pAssetFactoryLoader) override;

	bool LoadAsset(
		const std::string& pFilepath,
		const std::string& pFilename,
		std::shared_ptr<Asset>& pAsset) override;

	void UnloadAsset(Asset* pAsset) override;

private:
	TextureAssetLoaderInjector mInjector;
};

