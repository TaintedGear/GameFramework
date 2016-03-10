#pragma once

#include "AssetLoader.h"
#include "PCH.h"
#include "Texture2D.h"
#include "Renderer.h"

class Texture2DAssetLoader : public AssetLoader<Texture2D>
{
public:
	Texture2DAssetLoader();
	virtual ~Texture2DAssetLoader();

	bool StartupLoader(std::weak_ptr<class Renderer> renderer);

	bool LoadAsset(std::shared_ptr<Texture2D> unloadedAsset) override;
	void UnloadAsset(Texture2D* asset) override;

private:
	std::weak_ptr<class Renderer> mWeakRenderer;
};