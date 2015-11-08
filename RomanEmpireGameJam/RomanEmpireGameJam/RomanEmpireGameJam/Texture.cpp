#include "Texture.h"
#include "Log.h"

Texture::Texture(const std::string& pAssetFilepath, const std::string& pAssetFilename)
	:
	Asset(pAssetFilepath, pAssetFilename)
, mSDLTexture(nullptr)
{
}

Texture::~Texture()
{
}

//------------------------------------------//
// Texture::Create				
//------------------------------------------//
bool Texture::Create(SDL_Texture* pSDLTexture)
{
	if (pSDLTexture == nullptr)
	{
		// Failed to create texture
		Log::GetLog().LogHighMsg("Failed to create texture with path " + mAssetFilePath);
		return false;
	}

	mSDLTexture = pSDLTexture;

	return true;
}

//------------------------------------------//
// Texture::Release				
//------------------------------------------//
void Texture::Release()
{
	if (mSDLTexture)
	{
		SDL_DestroyTexture(mSDLTexture);
		mSDLTexture = nullptr;
	}
}
