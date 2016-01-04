#pragma once

#include "AssetLoader.h"
#include "PCH.h"
#include "Texture2D.h"

class Texture2DAssetLoader : public AssetLoader<Texture2D>
{
public:
	Texture2DAssetLoader();
	virtual ~Texture2DAssetLoader();

	bool LoadAsset(std::shared_ptr<Texture2D> unloadedAsset) override;
	void UnloadAsset(Texture2D* asset) override;
};