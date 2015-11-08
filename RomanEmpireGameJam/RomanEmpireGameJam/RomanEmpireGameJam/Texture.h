#pragma once

#include "Asset.h"
#include "PCH.h"

class Texture : public Asset
{
public:
	Texture(const std::string& pAssetFilepath, const std::string& pAssetFilename);
	virtual ~Texture();

	virtual bool Create(SDL_Texture* pSDLTexture);
	virtual void Release();

protected:
	SDL_Texture* mSDLTexture;
};

